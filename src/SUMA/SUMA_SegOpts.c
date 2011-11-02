#include "SUMA_suma.h"
#include "SUMA_SegOpts.h"
#include "SUMA_SegFunc.h"

static char shelp_GenPriors[] = {
"3dGenPriors produces classification priors based on voxel signatures.\n"
"At this stage, its main purpose is to speed up the performance of\n"
"3dSignatures when using the probablilistic method as opposed to SVM.\n"
"\n"
"Example:\n"
"3dGenPriors      -sig sigs+orig \\n"
"                 -tdist train.niml.td \\n"
"                 -pprefix anat.p \\n"
"                 -cprefix anat.c   \\n"
"                 -labeltable DSC.niml.lt \\n"
"                 -do pc   \n"
"\n"
"Options:\n"
"   -sig SIGS: Signatures dataset. A dataset with F features per voxel.\n"
"   -tdist TDIST: Training results. This file is generated by 3dSignatures.\n"
"                 ONLY training files generated by 3dSignatures' method 'prob'\n"
"                 can be used by this program. The number of features in this\n"
"                 file should match the number of features (F) in SIGS\n"
"                 This file also contains the names of the K classes that\n"
"                 will be references in the output datasets\n"
"\n"
"   -prefix PREF: Specify root prefix and let program suffix it for output \n"
"                 Volumes. This way you need not use the -*prefix options\n"
"                 below.\n"
"   -pprefix PPREF: Prefix for probability dset\n"
"   -cprefix CPREF: Prefix for class dset\n"
"   If you use -regroup_classes then you can also specify:\n"
"     -pgprefix PGPREF, and -cgprefix CGPREF\n"
"   -labeltable LTFILE: Labeltable to attach to output dset\n"
"                       This labeltable should contain all the classes\n"
"                       in TDIST\n"
"   -cmask CMASK: Provide cmask expression. Voxels where expression is 0\n"
"                 are excluded from computations\n"
"   -mask MASK: Provide mask dset\n"
"   -mrange M0 M1: Consider MASK only for values between M0 and M1, inclusive\n"
"   -do WHAT: Specify the output that this program should create.\n"
"             Each character in WHAT specifies an output. \n"
"             a 'c' produces the most likely class\n"
"             a 'p' produces probability of belonging to a class\n"
"             'pc' produces both of the above and that is the default.\n"
"             You'd be deranged to use anything else at the moment.\n"
"   -debug DBG: Set debug level\n"
"   -vox_debug 1D_DBG_INDEX: 1D index of voxel to debug.\n"
"       OR\n"
"   -vox_debug I J K: where I, J, K are the 3D voxel indices \n"
"                     (not RAI coordinates in mm)\n"
"   -vox_debug_file DBG_OUTPUT_FILE: File in which debug information is output\n"
"   -uid UID : User identifier string. It is used to generate names for\n"
"              temporary files to speed up the process. \n"
"              You must use different UID for different subjects otherwise\n"
"              you will run the risk of using bad temporary files.\n"
"              By default, uid is set to a random string.\n"
"   -use_tmp: Use temporary storage to speed up the program (see -uid )\n"
"             This is the default\n"
"   -no_tmp: Opposite of use_tmp\n"
"   -pset PSET: Reuse probability output from an earlier run.\n"
"   -cset CSET: Reuse classification output from an earlier run.\n"
"   -regroup_classes 'C1 C2 C3': Regroup classes into parent classes C1 C2 C3\n"
"                                For this to work, the original classes must \n"
"                                be named something like C1.*, C2.*, etc.\n"
"        This option can be used to replace @RegroupLabels script.\n"
"        For example:\n"
"        3dGenPriors      -sig sigs+orig \\\n"
"                         -tdist train.niml.td \\\n"
"                         -pprefix anat.p \\\n"
"                         -cprefix anat.c   \\\n"
"                         -labeltable DSC.niml.lt \\\n"
"                         -do pc   \\\n"
"                         -regroup_classes  'CSF GM WM Out'\n"
"\n"
"    or if you have the output already, you can do:\n"
"\n"
"       3dGenPriors      -sig sigs+orig \\\n"
"                         -tdist train.niml.td \\\n"
"                         -pset anat.p \\\n"
"                         -cset anat.c   \\\n"
"                         -labeltable DSC.niml.lt \\\n"
"                         -do pc   \\\n"
"                         -regroup_classes  'CSF GM WM Out'\n"           
"\n"
};

static char shelp_Seg[] = {
"3dSeg segments brain volumes into tissue classes.\n"
"\n"
"Examples: (All examples can do without the -gold* options)\n"
"  Case A: Segmenting a T1 volume with a brain mask available\n"
"  A.1:  Brain mask and MRF only.\n"
"  3dSeg    -anat banat+orig     \\\n"
"           -mask anat.ns+orig   \\\n"
"           -gold goldseg+orig   -gold_bias goldbias+orig   \\\n"
"           -classes 'CSF ; GM ; WM' \\\n"
"           -Bmrf 1.0            \\\n"
"           -bias_classes 'GM ; WM' -bias_fwhm 25 \\\n"
"           -prefix case.A.1  -overwrite    \\\n"
"\n"
"  A.2:  Adding average mixing fraction constraint derived from\n"
"        population based spatial priors, and preserving the weighting\n"
"        throughout the segmentation.\n"
"  3dSeg    -anat banat+orig     \\\n"
"           -mask anat.ns+orig   \\\n"
"           -gold goldseg+orig   -gold_bias goldbias+orig   \\\n"
"           -classes 'CSF ; GM ; WM' \\\n"
"           -bias_classes 'GM ; WM' -bias_fwhm 25 \\\n"
"           -prefix case.A.2  -overwrite    \\\n"
"           -mixfrac WHOLE_BRAIN \\\n"
"           -Bmrf 1.0 -main_N 4           \\\n"
"\n"
"\n"
};

static HELP_OPT SegOptList[] = {
   {  "-anat", 
      "-anat ANAT: ANAT is the volume to segment", 
      NULL },
   {  "-mask", 
      "-mask MASK: MASK only non-zero voxels in MASK are analyzed.\n"
      "            MASK is necessary when no voxelwise priors are\n"
      "            available.\n", 
      NULL },
   {  "-classes", 
      "-classes 'CLASS_STRING': CLASS_STRING is a semicolon delimited\n"
      "                         string of class labels. At the moment\n"
      "                         CLASS_STRING can only be 'CSF; GM; WM'\n", 
      NULL},
   {  "-Bmrf",
      "-Bmrf BMRF: Weighting factor controlling influence of MRF step. \n"
      "            BMRF = 0.0 means no MRF, 1.0 is typical, the larger BMRF\n"
      "            the stronger the MRF. Use -Bmrf when you have no voxelwise\n"
      "            priors.\n",
      "1.0" },           
   {  "-bias_classes",
      "-bias_classes 'BIAS_CLASS_STRING': A semcolon demlimited string of \n"
      "                                   classes that contribute to the \n"
      "                                   estimation of the bias field.\n",
      "'GM; WM'" },
   {  "-bias_fwhm BIAS_FWHM: The amount of blurring used when estimating the\n"
      "                      field bias with the Wells method [].\n",
      "25.0" },
   {  "-prefix PREF: PREF is the prefix for all output volume that are not \n"
      "              debugging related.\n", 
      "Segsy" },
   {  "-overwrite",
      "-overwrite: An option common to almost all AFNI programs. It is \n"
      "            automatically turned on if you provide no PREF.\n",
      NULL },
   {  "-mixfrac 'MIXFRAC': MIXFRAC sets up the volume-wide (within mask)\n"
      "                    tissue fractions while initializing the \n"
      "                    segmentation. You can specify the mixing fractions\n"
      "                    directly such as with '0.1 0.45 0.45', or with\n"
      "                    the following special flags:\n"
      "              XXX\n",
      "UNI" },    
   {  NULL, NULL, NULL  }
};

void GenPriors_usage(void) 
{
   int i = 0;
   
   ENTRY("GenPriors_usage");
   
   
   printf( "%s", shelp_GenPriors );
   EXRETURN;
}

void Seg_usage(void) 
{
   int i = 0;
   
   ENTRY("Seg_usage");
   printf( "%s", shelp_Seg );
   
   
   EXRETURN;
}

SEG_OPTS *SegOpt_Struct()
{
   SEG_OPTS *Opt=NULL;
   
   ENTRY("SegOpt_Struct");
   Opt = (SEG_OPTS *)calloc(1, sizeof(SEG_OPTS));
   
   Opt->ps = NULL;
   Opt->helpfunc = NULL;
   Opt->aset_name = NULL;
   Opt->mset_name = NULL;
   Opt->sig_name = NULL;
   Opt->gold_name = NULL;
   Opt->gold_bias_name = NULL;
   Opt->this_pset_name = NULL;
   Opt->this_cset_name = NULL;
   Opt->this_fset_name = NULL;
   Opt->this_xset_name = NULL;
   Opt->ndist_name = NULL;
   Opt->uid[0] = '\0';
   Opt->proot = NULL;
   Opt->prefix = NULL;
   Opt->gold = NULL;
   Opt->gold_bias = NULL;
   Opt->aset = NULL;
   Opt->mset = NULL;
   Opt->gset = NULL;
   Opt->sig = NULL;
   Opt->ndist = NULL;
   Opt->pset = NULL;
   Opt->cset = NULL;
   Opt->fset = NULL;
   Opt->xset = NULL;
   Opt->debug = 0;
   Opt->idbg = Opt->kdbg = Opt->jdbg = -1;
   Opt->binwidth = 0; 
   Opt->feats=NULL;
   Opt->clss=NULL;
   Opt->Other=0;
   Opt->keys=NULL;
   Opt->mixopt = NULL;
   Opt->mixfrac=NULL;
   Opt->UseTmp = 0; 
   Opt->logp = 0;
   Opt->VoxDbg = -1;
   Opt->VoxDbg3[0] = Opt->VoxDbg3[1] = Opt->VoxDbg3[2] = -1;
   Opt->VoxDbgOut = stdout;
   Opt->rescale_p = 0;
   Opt->openmp = 0;
   Opt->labeltable_name = NULL;
   Opt->smode = STORAGE_BY_BRICK;
   Opt->bias_classes = NULL;
   Opt->pweight = 0;
   Opt->N_biasgroups=0;
   Opt->bias_param = 25;
   Opt->bias_meth = "Wells";
   Opt->cmask = NULL;
   Opt->dimcmask = 0;
   Opt->cmask_count=0;
   Opt->mask_bot = 1.0;
   Opt->mask_top = -1.0;
   Opt->DO_p = FALSE;
   Opt->DO_f = FALSE;
   Opt->DO_c = FALSE;
   Opt->DO_x = FALSE;
   Opt->group_classes = NULL;
   Opt->group_keys = NULL;
   
   Opt->fitmeth = 0;
   Opt->N_enhance_cset_init = 0;
   Opt->N_main = 0;
   Opt->clust_cset_init = 0;
   
   Opt->cs = NULL;
   Opt->Gcs = NULL;
   
   Opt->B = 1.0;
   Opt->T = 1.0;
   
   Opt->na = 8.0;
   
   Opt->edge = 0.0;
   
   Opt->hist = NULL;
   
   Opt->priCgA = NULL; /* Prob. class given features */
   Opt->wA=-1.0;
   Opt->priCgAname = NULL;
   
   Opt->priCgL = NULL; /* Prob. class given location */
   Opt->wL=-1.0;
   Opt->priCgLname = NULL;
   
   Opt->priCgALL = NULL; /* Prob. class */
   Opt->priCgALLname = NULL;
   
   Opt->Bset = NULL;
   Opt->pstCgALL = NULL;
   Opt->pCgN = NULL;
   Opt->pstCgALLname = NULL;
   Opt->Bsetname = NULL;
   Opt->Split = NULL;
   
   Opt->blur_meth = SEG_BIM;
   RETURN(Opt);
}

SEG_OPTS *free_SegOpts(SEG_OPTS *Opt) {
   if (!Opt) return(NULL);
   if (Opt->gold) DSET_delete(Opt->gold); Opt->gold = NULL;
   if (Opt->gold_bias) DSET_delete(Opt->gold_bias); Opt->gold_bias = NULL;
   if (Opt->aset) DSET_delete(Opt->aset); Opt->aset = NULL;
   if (Opt->mset) DSET_delete(Opt->mset); Opt->mset = NULL;
   if (Opt->pset) DSET_delete(Opt->pset); Opt->pset = NULL;
   if (Opt->cset) DSET_delete(Opt->cset); Opt->cset = NULL;
   if (Opt->fset) DSET_delete(Opt->fset); Opt->fset = NULL;
   if (Opt->xset) DSET_delete(Opt->xset); Opt->xset = NULL;
   if (Opt->gset) DSET_delete(Opt->gset); Opt->gset = NULL;
   if (Opt->sig)  DSET_delete(Opt->sig); Opt->sig = NULL;
   if (Opt->priCgA)  DSET_delete(Opt->priCgA); Opt->priCgA = NULL;
   if (Opt->priCgL)  DSET_delete(Opt->priCgL); Opt->priCgL = NULL;
   if (Opt->priCgALL)  DSET_delete(Opt->priCgALL); Opt->priCgALL = NULL;
   if (Opt->feats) NI_delete_str_array(Opt->feats);Opt->feats = NULL;
   if (Opt->clss)  NI_delete_str_array(Opt->clss );Opt->clss = NULL;
   if (Opt->keys) free(Opt->keys); Opt->keys = NULL;
   if (Opt->mixfrac) free(Opt->mixfrac);Opt->mixfrac = NULL;
   if (Opt->VoxDbgOut && Opt->VoxDbgOut != stdout) fclose(Opt->VoxDbgOut);
      Opt->VoxDbgOut  = NULL;
   if (Opt->prefix) free(Opt->prefix);Opt->prefix = NULL;
   if (Opt->frefix) free(Opt->frefix);Opt->frefix = NULL;
   if (Opt->crefix) free(Opt->crefix);Opt->crefix = NULL;
   if (Opt->xrefix) free(Opt->xrefix);Opt->xrefix  = NULL;
   if (Opt->cgrefix) free(Opt->cgrefix); Opt->cgrefix = NULL;
   if (Opt->pgrefix) free(Opt->pgrefix); Opt->pgrefix = NULL;

   if (Opt->group_classes) NI_delete_str_array(Opt->group_classes) ;
      Opt->group_classes = NULL;
   if (Opt->group_keys) free(Opt->group_keys); Opt->group_keys = NULL;
   if (Opt->cs) Opt->cs = SUMA_Free_Class_Stat(Opt->cs);  
   if (Opt->Gcs) Opt->cs = SUMA_Free_Class_Stat(Opt->Gcs);  
   if (Opt->hist) free(Opt->hist); Opt->hist=NULL;
   if (Opt->Split) free(Opt->Split); Opt->Split=NULL;
   free(Opt); Opt = NULL;
   return(NULL);
}


SEG_OPTS *Seg_ParseInput (SEG_OPTS *Opt, char *argv[], int argc)
{
   static char FuncName[]={"Seg_ParseInput"}; 
   int kar, i, ind, exists;
   char *outname, cview[10];
   int brk = 0;
   SUMA_GENERIC_ARGV_PARSE *ps=NULL;

   ENTRY("Seg_ParseInput");
   
   brk = 0;
   kar = 1;
	while (kar < argc) { /* loop accross command ine options */
		/*fprintf(stdout, "%s verbose: Parsing command line...\n", FuncName);*/
		if (strcmp(argv[kar], "-h") == 0 || strcmp(argv[kar], "-help") == 0) {
			 Opt->helpfunc();
          exit (0);
		}
      
 		SUMA_SKIP_COMMON_OPTIONS(brk, kar);
     
      #ifdef USE_TRACING
            if( strncmp(argv[kar],"-trace",5) == 0 ){
               DBG_trace = 1 ;
               brk = 1 ;
            }
            if( strncmp(argv[kar],"-TRACE",5) == 0 ){  
               DBG_trace = 2 ;
               brk = 1 ;
            }
      #endif
      
      if (!brk && (strcmp(argv[kar], "-debug") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -debug \n");
				exit (1);
			}
			Opt->debug = atoi(argv[kar]);
         brk = 1;
		}      
      
      if (!brk && (strcmp(argv[kar], "-talk_afni") == 0)) {
         Opt->ps->cs->talk_suma = 1;
         brk = 1;
		}      
      
      if (!brk && (strcmp(argv[kar], "-do") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -do \n");
				exit (1);
			}
			if (strchr(argv[kar], 'c')) Opt->DO_c = 1;
			if (strchr(argv[kar], 'f')) Opt->DO_f = 1;
			if (strchr(argv[kar], 'x')) Opt->DO_x = 1;
			if (strchr(argv[kar], 'p')) Opt->DO_p = 1;
         
         brk = 1;
		}      

      if (!brk && (strcmp(argv[kar], "-L2") == 0)) {
			Opt->fitmeth = SEG_LSQFIT;
         brk = 1;
		}      

      if (!brk && (strcmp(argv[kar], "-L1") == 0)) {
			Opt->fitmeth = SEG_L1FIT;
         brk = 1;
		}      

      if (!brk && (strcmp(argv[kar], "-openmp") == 0)) {
			Opt->openmp = 1;
         brk = 1;
		}   
         
      if (!brk && (strcmp(argv[kar], "-no_openmp") == 0)) {
			Opt->openmp = 0;
         brk = 1;
		}      

      if (!brk && (strcmp(argv[kar], "-pweight") == 0)) {
			Opt->pweight = 1;
         brk = 1;
		}      

      if (!brk && (strcmp(argv[kar], "-no_pweight") == 0)) {
			Opt->pweight = 0;
         brk = 1;
		}      

      if (!brk && (strcmp(argv[kar], "-no_edge") == 0)) {
			Opt->edge = 0;
         brk = 1;
		}      

      if (!brk && (strcmp(argv[kar], "-edge") == 0)) {
			Opt->edge = 1;
         brk = 1;
		}
      
      if (!brk && (strcmp(argv[kar], "-edge1") == 0)) {
			Opt->edge = 1;
         brk = 1;
		}      

      if (!brk && (strcmp(argv[kar], "-edge2") == 0)) {
			Opt->edge = 2;
         brk = 1;
		}      

      if (!brk && (strcmp(argv[kar], "-vox_debug") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need 1D vox index after -vox_debug \n");
				exit (1);
			}
         if (kar+2<argc) { /* see if we have ijk */
            int iii, jjj, kkk;
            if (argv[kar][0]!='-' && argv[kar][1]!='-' && argv[kar][2]!='-' &&
                (iii = atoi(argv[kar  ])) >= 0 &&
                (jjj = atoi(argv[kar+1])) >= 0 && 
                (kkk = atoi(argv[kar+2])) >= 0 ) {
               Opt->VoxDbg3[0]=iii;
               Opt->VoxDbg3[1]=jjj;
               Opt->VoxDbg3[2]=kkk;    
               ++kar; ++kar;
            } 
         }
			if (Opt->VoxDbg3[0] < 0) {
            Opt->VoxDbg = atoi(argv[kar]);
         }
         brk = 1;
		}      

      if (!brk && (strcmp(argv[kar], "-vox_debug_file") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need filename after -vox_debug_file \n");
				exit (1);
			}
			Opt->VoxDbgOut = fopen(argv[kar],"w");
         brk = 1;
		}      
      
      if (strcmp(argv[kar],"-logp") == 0 ) {
         Opt->logp = 1;
         brk = 1;
      }
      
      if (strcmp(argv[kar],"-p") == 0 ) {
         Opt->logp = 0;
         brk = 1;
      }
      
      if( strcmp(argv[kar],"-use_tmp") == 0 ){
         Opt->UseTmp = 1 ;
         brk = 1;
      }

      if( strcmp(argv[kar],"-no_tmp") == 0 ){
         Opt->UseTmp = 0 ;
         brk = 1;
      }
      
      if (!brk && (strcmp(argv[kar], "-vox_debug") == 0)) {
         kar ++;
			if (kar+2 >= argc)  {
		  		fprintf (stderr, "need 3 arguments after -vox_debug \n");
				exit (1);
			}
			Opt->idbg = atoi(argv[kar]); ++kar;
         Opt->jdbg = atoi(argv[kar]); ++kar;
         Opt->kdbg = atoi(argv[kar]);
         brk = 1;
		} 
     
      if (!brk && (strcmp(argv[kar], "-cmask") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		ERROR_exit("-cmask option requires a following argument!\n");
			}
			Opt->cmask = EDT_calcmask( argv[kar] , &(Opt->dimcmask), 0 ) ;
         if( Opt->cmask == NULL ) ERROR_exit("Can't compute -cmask!\n");
         brk = 1;
		}
      
      if (!brk && (strcmp(argv[kar], "-mask") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -mset \n");
				exit (1);
			}
			Opt->mset_name = argv[kar];
         brk = 1;
      }
      
      if( !brk && (strncmp(argv[kar],"-mrange",5) == 0) ){
         if( kar+2 >= argc )
           ERROR_exit("-mrange option requires 2 following arguments!\n");
         Opt->mask_bot = strtod( argv[++kar] , NULL ) ;
         Opt->mask_top = strtod( argv[++kar] , NULL ) ;
         if( Opt->mask_top < Opt->mask_bot )
           ERROR_exit("-mrange inputs are illegal!\n") ;
         brk = 1;
      }
      
      if (!brk && (strcmp(argv[kar], "-anat") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -anat \n");
				exit (1);
			}
			Opt->aset_name = argv[kar];
         brk = 1;
		}
            
      if (!brk && (strcmp(argv[kar], "-sig") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -sig \n");
				exit (1);
			}
			Opt->sig_name = argv[kar];
         brk = 1;
		}
      
      if (!brk && (strcmp(argv[kar], "-pset") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -pset \n");
				exit (1);
			}
			Opt->this_pset_name = argv[kar];
         brk = 1;
		}
      
      if (!brk && (strcmp(argv[kar], "-gold") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -gold \n");
				exit (1);
			}
			Opt->gold_name = argv[kar];
         brk = 1;
		}

      if (!brk && (strcmp(argv[kar], "-gold_bias") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -gold_bias \n");
				exit (1);
			}
			Opt->gold_bias_name = argv[kar];
         brk = 1;
		}

      if (!brk && (strcmp(argv[kar], "-pstCgALL") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -pstCgALL \n");
				exit (1);
			}
			Opt->pstCgALLname = argv[kar];
         brk = 1;
		}
      
      if (!brk && (strcmp(argv[kar], "-priCgL") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -priCgL \n");
				exit (1);
			}
			Opt->priCgLname = argv[kar];
         brk = 1;
		}
      
      if (!brk && (strcmp(argv[kar], "-priCgALL") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -priCgALL \n");
				exit (1);
			}
			Opt->priCgALLname = argv[kar];
         brk = 1;
		}
      
      if (!brk && (strcmp(argv[kar], "-wL") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -wL \n");
				exit (1);
			}
			Opt->wL = atof(argv[kar]);
         if (Opt->wL < 0.0 || Opt->wL > 1.0) {
            SUMA_S_Errv("-wL must be between 0 and 1.0, have %s", argv[kar]);
            exit(1);
         }
         brk = 1;
		}
      
      if (!brk && (strcmp(argv[kar], "-priCgA") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -priCgA \n");
				exit (1);
			}
			Opt->priCgAname = argv[kar];
         brk = 1;
		}
      
      if (!brk && (strcmp(argv[kar], "-wA") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -wA \n");
				exit (1);
			}
			Opt->wA = atof(argv[kar]);
         if (Opt->wA < 0.0 || Opt->wA > 1.0) {
            SUMA_S_Errv("-wA must be between 0 and 1.0, have %s", argv[kar]);
            exit(1);
         }
         brk = 1;
		}
      
      if (!brk && (strcmp(argv[kar], "-cset") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -cset \n");
				exit (1);
			}
			Opt->this_cset_name = argv[kar];
         brk = 1;
		}

      if (!brk && (strcmp(argv[kar], "-fset") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -fset \n");
				exit (1);
			}
			Opt->this_fset_name = argv[kar];
         brk = 1;
		}
      
      if (!brk && (strcmp(argv[kar], "-xset") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -xset \n");
				exit (1);
			}
			Opt->this_xset_name = argv[kar];
         brk = 1;
		}
      
      if (!brk && (strcmp(argv[kar], "-tdist") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -tdist \n");
				exit (1);
			}
			Opt->ndist_name = argv[kar];
         brk = 1;
		}

      if (!brk && (strcmp(argv[kar], "-labeltable") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -labeltable \n");
				exit (1);
			}
			Opt->labeltable_name = argv[kar];
         brk = 1;
		}

      if (!brk && (strcmp(argv[kar], "-sphere_hood") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -sphere_hood \n");
				exit (1);
			}
			Opt->na = atof(argv[kar]);
         brk = 1;
		} 
      
      if (!brk && (strcmp(argv[kar], "-mask") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -mask \n");
				exit (1);
			}
			Opt->mset_name = argv[kar];
         brk = 1;
		}
      
      if (!brk && (strcmp(argv[kar], "-blur_meth") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -blur_meth \n");
				exit (1);
			}
			if (!strcmp(argv[kar],"BIM")) Opt->blur_meth = SEG_BIM;
         else if (!strncmp(argv[kar],"LS",2)) Opt->blur_meth = SEG_LSB;
         else {
            SUMA_S_Errv("-blur_meth %s not valid\n", argv[kar]);
            exit(1);
         }
         brk = 1;
		}
            
      if (!brk && (strcmp(argv[kar], "-prefix") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -prefix \n");
				exit (1);
			}
			Opt->smode = storage_mode_from_filename(argv[kar]);
         Opt->proot = argv[kar];
         Opt->prefix = (char*)calloc(strlen(argv[kar])+20, sizeof(char));
         Opt->crefix = (char*)calloc(strlen(argv[kar])+20, sizeof(char));
         Opt->pgrefix = (char*)calloc(strlen(argv[kar])+20, sizeof(char));
         Opt->cgrefix = (char*)calloc(strlen(argv[kar])+20, sizeof(char));
         Opt->frefix = (char*)calloc(strlen(argv[kar])+20, sizeof(char));
         Opt->xrefix = (char*)calloc(strlen(argv[kar])+20, sizeof(char));
         sprintf(Opt->prefix,"%s.p", argv[kar]);
         sprintf(Opt->pgrefix,"%s.pg", argv[kar]);
         sprintf(Opt->crefix,"%s.c", argv[kar]);
         sprintf(Opt->cgrefix,"%s.cg", argv[kar]);
         sprintf(Opt->frefix,"%s.f", argv[kar]);
         sprintf(Opt->xrefix,"%s.x", argv[kar]);
         brk = 1;
		}
      
      if (!brk && (strcmp(argv[kar], "-pprefix") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -pprefix \n");
				exit (1);
			}
			Opt->smode = storage_mode_from_filename(argv[kar]);
         Opt->prefix = (char*)calloc(strlen(argv[kar])+20, sizeof(char));
         sprintf(Opt->prefix,"%s", argv[kar]);
         brk = 1;
		}
      
      if (!brk && (strcmp(argv[kar], "-fprefix") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -fprefix \n");
				exit (1);
			}
			Opt->smode = storage_mode_from_filename(argv[kar]);
         Opt->frefix = (char*)calloc(strlen(argv[kar])+20, sizeof(char));
         sprintf(Opt->frefix,"%s", argv[kar]);
         brk = 1;
		}
      
      if (!brk && (strcmp(argv[kar], "-cprefix") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -cprefix \n");
				exit (1);
			}
			Opt->smode = storage_mode_from_filename(argv[kar]);
         Opt->crefix = (char*)calloc(strlen(argv[kar])+20, sizeof(char));
         sprintf(Opt->crefix,"%s", argv[kar]);
         brk = 1;
		}
      
      if (!brk && (strcmp(argv[kar], "-cgprefix") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -cgprefix \n");
				exit (1);
			}
			Opt->smode = storage_mode_from_filename(argv[kar]);
         Opt->cgrefix = (char*)calloc(strlen(argv[kar])+20, sizeof(char));
         sprintf(Opt->cgrefix,"%s", argv[kar]);
         brk = 1;
		}
      
      if (!brk && (strcmp(argv[kar], "-pgprefix") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -pgprefix \n");
				exit (1);
			}
			Opt->smode = storage_mode_from_filename(argv[kar]);
         Opt->pgrefix = (char*)calloc(strlen(argv[kar])+20, sizeof(char));
         sprintf(Opt->pgrefix,"%s", argv[kar]);
         brk = 1;
		}
      
      if (!brk && (strcmp(argv[kar], "-xprefix") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -xprefix \n");
				exit (1);
			}
			Opt->smode = storage_mode_from_filename(argv[kar]);
         Opt->xrefix = (char*)calloc(strlen(argv[kar])+20, sizeof(char));
         sprintf(Opt->xrefix,"%s", argv[kar]);
         brk = 1;
		}
      
      if (!brk && (strcmp(argv[kar], "-bias_classes") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -bias_classes \n");
				exit (1);
			}
			Opt->bias_classes = argv[kar];
         brk = 1;
		}
      
      if (!brk && (strcmp(argv[kar], "-group_classes") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -group_classes \n");
				exit (1);
			}
			Opt->group_classes = NI_strict_decode_string_list(argv[kar] ,";");
         brk = 1;
		}

      if (!brk && (strcmp(argv[kar], "-group_keys") == 0)) {
         NI_str_array *nstr=NULL; int ii;
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -group_keys \n");
				exit (1);
			}
			if (!(nstr = NI_strict_decode_string_list(argv[kar] ,";, "))){
            ERROR_exit("Bad option %s after -group_keys", argv[kar]);
         }
         Opt->group_keys = (int *)calloc(nstr->num, sizeof(int));
         for (ii=0;ii<nstr->num; ++ii) 
            Opt->group_keys[ii] = strtol(nstr->str[ii],NULL,10);
         NI_delete_str_array(nstr);nstr=NULL;
         brk = 1;
		}
      
      if (!brk && (strcmp(argv[kar], "-classes") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -classes \n");
				exit (1);
			}
			Opt->clss = NI_strict_decode_string_list(argv[kar] ,";, ");
         brk = 1;
		}
      
      if (!brk && (strcmp(argv[kar], "-split_classes") == 0)) {
         NI_str_array *nstr=NULL; int ii;
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -split_classes \n");
				exit (1);
			}
			nstr = NI_strict_decode_string_list(argv[kar] ,";, ");
         Opt->Split = (int *)calloc(nstr->num+1, sizeof(int));
         for (ii=0;ii<nstr->num; ++ii) {
            Opt->Split[ii] = strtol(nstr->str[ii],NULL,10);
            if (Opt->Split[ii]<1 || Opt->Split[ii]>9) {
               SUMA_S_Errv("Bad split value of %d in %s\n", 
                           Opt->Split[ii], argv[kar]);
               exit(1);
            }
         }
         Opt->Split[nstr->num]=-1; /* plug */
         
         brk = 1;
		}

      if (!brk && (strcmp(argv[kar], "-other") == 0)) {
         Opt->Other = 1;
         brk = 1;
      }
      
      if (!brk && (strcmp(argv[kar], "-no_other") == 0)) {
         Opt->Other = 0;
         brk = 1;
      }
      
      if (!brk && (strcmp(argv[kar], "-keys") == 0)) {
         NI_str_array *nstr=NULL; int ii;
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -keys \n");
				exit (1);
			}
			if (!(nstr = NI_strict_decode_string_list(argv[kar] ,";, "))){
            ERROR_exit("Bad option %s after -keys", argv[kar]);
         }
         Opt->keys = (int *)calloc(nstr->num, sizeof(int));
         for (ii=0;ii<nstr->num; ++ii) 
            Opt->keys[ii] = strtol(nstr->str[ii],NULL,10);
         NI_delete_str_array(nstr);nstr=NULL;
         brk = 1;
		}
      
      if (!brk && (strcmp(argv[kar], "-bias_order") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need integer after -bias_order \n");
				exit (1);
			}
			Opt->bias_param = atof(argv[kar]);
         Opt->bias_meth = "Poly";
         brk = 1;
		}
      
      if (!brk && (strcmp(argv[kar], "-bias_fwhm") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need integer after -bias_fwhm \n");
				exit (1);
			}
			Opt->bias_param = atof(argv[kar]);
         Opt->bias_meth = "Wells";
         brk = 1;
		}
      
      if (!brk && (strcmp(argv[kar], "-enhance_cset_init") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need integer after -enhance_cset_init \n");
				exit (1);
			}
			Opt->N_enhance_cset_init = atoi(argv[kar]);
         SUMA_S_Err("Option not in use at the moment");
         brk = 1;
		}

      if (!brk && (strcmp(argv[kar], "-main_N") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need integer after -main_N \n");
				exit (1);
			}
			Opt->N_main = atoi(argv[kar]);
         brk = 1;
		}
      
      if (!brk && (strcmp(argv[kar], "-clust_cset_init") == 0)) {
			Opt->clust_cset_init = 1;
         brk = 1;
      }
      
      if (!brk && (strcmp(argv[kar], "-no_clust_cset_init") == 0)) {
			Opt->clust_cset_init = 0;
         brk = 1;
      }
      
      if (!brk && (strcmp(argv[kar], "-uid") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -uid \n");
				exit (1);
			}
			snprintf(Opt->uid,128,"%s",argv[kar]);
         brk = 1;
		}
      
      if (!brk && (strcmp(argv[kar], "-mixfrac") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need argument after -mixfrac \n");
				exit (1);
			}
			Opt->mixopt = argv[kar];
         brk = 1;
		}

      if (!brk && (strcmp(argv[kar], "-Bmrf") == 0)) {
         kar ++;
			if (kar >= argc)  {
		  		fprintf (stderr, "need value after -Bmrf \n");
				exit (1);
			}
			Opt->B = atof(argv[kar]);
         brk = 1;
		}
      
      if (!brk) {
			fprintf (stderr,"Option %s not understood. \n"
                         "Try -help for usage\n", argv[kar]);
			exit (1);
		} else {	
			brk = 0;
			kar ++;
		}

   }
   
   if (!Opt->prefix) Opt->prefix = strdup("./GenPriorsOut.p");
   if (!Opt->frefix) Opt->frefix = strdup("./GenPriorsOut.f");
   if (!Opt->xrefix) Opt->xrefix = strdup("./GenPriorsOut.x");
   if (!Opt->crefix) Opt->crefix = strdup("./GenPriorsOut.c");
   if (Opt->uid[0]=='\0') UNIQ_idcode_fill(Opt->uid);

   RETURN(Opt);
}

byte *MaskSetup(SEG_OPTS *Opt, THD_3dim_dataset *aset, 
                THD_3dim_dataset **msetp, byte **cmaskp, int dimcmask, 
                float mask_bot, float mask_top, int *mcount) 
{ 
   byte *mmm=NULL;
   int ii=0, kk=0;
   byte *cmask = NULL;
   THD_3dim_dataset *mset = NULL;
   
   /* ------------- Mask business -----------------*/
   
   if (cmaskp) cmask = *cmaskp;
   if (msetp) mset = *msetp;
   
   if( mset == NULL ){
      mmm = NULL ;
      if( Opt->debug ) 
         INFO_message("%d voxels in the entire dataset (no mask)\n",
                     DSET_NVOX(aset)) ;
      *mcount = DSET_NVOX(aset);
   } else {
      if( DSET_NVOX(mset) != DSET_NVOX(aset) )
        ERROR_exit("Input and mask datasets are not same dimensions!\n");
      mmm = THD_makemask( mset , 0 , mask_bot, mask_top ) ;
      *mcount = THD_countmask( DSET_NVOX(mset) , mmm ) ;
      if( *mcount <= 0 ) {
         ERROR_message("No voxels in the mask!\n") ;
         return(NULL);
      }
      if( Opt->debug ) INFO_message("%d voxels in the mask\n",*mcount) ;
      DSET_delete(mset); *msetp=NULL;
   }

   if( cmask != NULL ){
      if( dimcmask != DSET_NVOX(aset) )
        ERROR_exit("Input and cmask datasets are not same dimensions!\n");
      if( mmm != NULL ){
         for( ii=0 ; ii < DSET_NVOX(aset) ; ii++ ) 
            mmm[ii] = (mmm[ii] && cmask[ii]) ;
         free(cmask) ; *cmaskp=NULL;
         *mcount = THD_countmask( DSET_NVOX(aset) , mmm ) ;
         if( *mcount <= 0 ) {
            ERROR_message("No voxels in the mask+cmask!\n") ;
            return(NULL);
         }
         if( Opt->debug ) 
            INFO_message("%d voxels in the mask+cmask\n",*mcount) ;
      } else {
         mmm = cmask ;
         *mcount = THD_countmask( DSET_NVOX(aset) , mmm ) ;
         if( *mcount <= 0 ) {
            ERROR_message("No voxels in the cmask!\n") ;
            return(NULL);
         }
         if( Opt->debug ) INFO_message("%d voxels in the cmask\n",*mcount) ;
      }
   }
   
   return(mmm);         
}

void *Seg_NI_read_file(char *fname) {
   char *niname = NULL;
   NI_stream ns = NULL;
   void *nel=NULL;
   
   ENTRY("Seg_NI_read_file");
   
   niname = (char *)malloc(sizeof(char)*(strlen(fname)+10));
   
   sprintf(niname,"file:%s",fname);
   
   ns = NI_stream_open(niname, "r");

   nel = NI_read_element(ns,1);
   
   NI_stream_close( ns ) ; ns = NULL;
   free(niname);
   
   RETURN(nel);
}

int SUMA_ShortizeDset(THD_3dim_dataset **dsetp, float thisfac) {
   static char FuncName[]={"SUMA_ShortizeDset"};
   char sprefix[THD_MAX_PREFIX+10];
   int i, j;
   byte *bb=NULL;
   short *sb=NULL;
   float bbf=0.0;
   
   THD_3dim_dataset *cpset=NULL, *dset=*dsetp;
   
   SUMA_ENTRY;
   
   if (!dset) {
      SUMA_S_Err("NULL *dsetp at input!");
      SUMA_RETURN(0);
   }
   
   sprintf(sprefix, "%s.s", dset->dblk->diskptr->prefix);
   NEW_SHORTY(dset, DSET_NVALS(dset), "ss.cp", cpset);      
   for (i=0; i<DSET_NVALS(dset); ++i) {
      if (DSET_BRICK_TYPE(dset,i) == MRI_byte) {
         bb = (byte *)DSET_ARRAY(dset,i);
         sb = (short *)DSET_ARRAY(cpset,i);
         if (thisfac <= 0.0) {
            for (j=0; j<DSET_NVOX(dset); ++j) {
               sb[j] = (short)bb[j];
            }
            thisfac = DSET_BRICK_FACTOR(dset,i);
         } else {
            bbf = DSET_BRICK_FACTOR(dset,i); if (bbf == 0.0f) bbf = 1.0;
            bbf = bbf/thisfac;
            for (j=0; j<DSET_NVOX(dset); ++j) {
               sb[j] = SHORTIZE((((float)bb[j])*bbf));
            }
         }
         EDIT_BRICK_FACTOR( cpset,i,thisfac ) ;
      } else {
         EDIT_substscale_brick(cpset, i, DSET_BRICK_TYPE(dset,i), 
                            DSET_ARRAY(dset,i), MRI_short, thisfac);
      }
   }
   DSET_delete(dset); dset = NULL; 
   *dsetp=cpset;

   SUMA_RETURN(1);
}
   
THD_3dim_dataset *Seg_load_dset( char *set_name ) {
   THD_3dim_dataset *dset=NULL, *sdset=NULL;
   int i=0;
   byte make_cp=0;
   char sprefix[THD_MAX_PREFIX+10];
   ENTRY("Seg_load_dset");
   
   dset = THD_open_dataset( set_name );
   if( !ISVALID_DSET(dset) ){
     fprintf(stderr,"**ERROR: can't open dataset %s\n",set_name) ;
     RETURN(NULL);
   }
   
   DSET_mallocize(dset)   ; DSET_load(dset);
   
   for (i=0; i<DSET_NVALS(dset); ++i) {
      if (DSET_BRICK_TYPE(dset,i) != MRI_short) {
         INFO_message("Sub-brick %d in %s not of type short.\n"
                       "Creating new short copy of dset ", 
                       i, DSET_PREFIX(dset));
         make_cp=1; break;
      }
   }
   
   if (make_cp) {
      if (!SUMA_ShortizeDset(&dset, -1.0)) {
         ERROR_exit("**ERROR: Failed to shortize");
      }
   }
   
   RETURN(dset);
}

int Seg_ClssAndKeys_from_dset(THD_3dim_dataset *dset, 
                              NI_str_array **nstrp, int **keysp) 
{
   ATR_string *atr=NULL;
   NI_str_array *nstr=NULL; 
   int *keys=NULL;
   NI_stream ns ;
   NI_element *nel ;
   int nn , ii ;
   Dtable *dt ;
   char **la , **lb ;
   
   if (!(atr = THD_find_string_atr( dset->dblk , "VALUE_LABEL_DTABLE" )))
      return(0);
   
   if (!(nel = (NI_element *)NI_read_element_fromstring(atr->ch))) {
      return (0);
   }

   /* see if element is OK for this purpose */

   if( NI_element_type(nel) != NI_ELEMENT_TYPE ){
     NI_free_element(nel) ; return (0) ;
   }

   if( nel->vec_len    <  1         ||  /* empty element?             */
       nel->vec_filled <  1         ||  /* no data was filled in?     */
       nel->vec_num    <  2         ||  /* less than 4 columns?       */
       nel->vec_typ[0] != NI_STRING ||  /* must be String, String     */
       nel->vec_typ[1] != NI_STRING   ){

     NI_free_element(nel) ; return (0) ;
   }

   la = (char **) nel->vec[0] ;  /* first column of String */
   lb = (char **) nel->vec[1] ;  /* second column of String */

   nn = nel->vec_filled ;
   ii = rint(sqrt(2*nn+1.0l)) ;
   if( ii < 7 ) ii = 7 ; else if( ii%2 == 0 ) ii++ ;

   /* make array, insert strings */
   nstr = SUMA_NI_string_vec_to_str_array(lb, nn);
   
   /* get keys */
   keys = (int *)calloc(nn, sizeof(int));
   for( ii=0 ; ii < nn ; ii++ )
     keys[ii] = strtol(la[ii], NULL, 10);

   NI_free_element(nel) ; 
   
   if (nstrp) {*nstrp = nstr; nstr=NULL;}
   else { nstr = SUMA_free_NI_str_array(nstr); }
   
   if (keysp) { *keysp = keys; keys=NULL; }
   else { free(keys); keys=NULL; }
   
   return (1) ;               
}
