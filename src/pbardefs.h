/* ZSS: New 256-color maps.
   Each new color map is added with 
   a call to PBAR_define_bigmap in pbar.c
*/

/* Color map for The Eickhoff and Zilles 
   Cytoarchitectonic data AllAreas_v12
   
  see matlab/MakeCytoArchColMaps.m
*/
static char CYTOARCH_ROI_256_CMD[] = {  
      "CytoArch_ROI_256 "
      "#84392e #018f67 #776b1b #01d9d4 #9f35b8 "
      "#f7d202 #2100cf #d494f6 #bbfa2d #fd2d74 "
      "#90c648 #c4516e #fe28fd #a83d26 #4fda69 "
      "#40fcf8 #c4589f #27abf3 #610051 #49f8c0 "
      "#ad185d #68f88d #d80491 #d92918 #2b649d "
      "#65bbea #772e83 #fed039 #0591b2 #ed2b3e "
      "#67a84b #cb7941 #7a2eb0 #39af94 #57fa28 "
      "#fb7dfd #a46b42 #13e94c #4b70f0 #c8cf33 "
      "#02e79a #fcae11 #96d7fb #42358b #0009fd "
      "#ff2bcf #9d9909 #173472 #fe7c31 #3780c8 "
      "#1041fe #f0d260 #a19349 #45ff8a #fd9376 "
      "#cf3fcc #c3c866 #059489 #3cfe59 #ff0091 "
      "#fbb3a1 #c8f104 #d92a70 #86ef42 #7b02ea "
      "#fde693 #b408b2 #1b52d4 #f687cd #8257b9 "
      "#88100b #fa03cb #e85783 #045602 #7d97fa "
      "#8cfe76 #1608a9 #fdff01 #ff56b9 #0d359a "
      "#b41335 #7b07ab #3dc0c5 #feab3d #6fc9af "
      "#0afdf9 #b9f760 #4cc50f #c067fe #fffb5f "
      "#df7e05 #ba00de #3d954b #c636f6 #05b7c2 "
      "#ac3d02 #0d7e3d #534fb4 #ac7119 #ab0a85 "
      "#0667a5 #17b80f #494be9 #860b3b #85c323 "
      "#6ddedd #3d888c #d5956d #378307 #390872 "
      "#8463ff #24f0c6 #d1b100 #02fc73 #90ffa8 "
      "#01c6fc #fd1017 #4407f2 #9b4450 #03b24b "
      "#a0428e #02bf89 #4d96ff #79490c #461ab6 "
      "#43d344 #b06dc9 #df4e04 #83d16f #04f025 "
      "#a2fee4 #e80153 #ffa6f8 #96f718 #5e83c0 "
      "#eb02f9 #bf0005 #cfa736 #0a7fdf #f685a0 "
      "#000a7a #e12ba0 #046372 #d1eb91 #740377 "
      "#39d6fc #708e1f #acb0fd #fd52fa #01840a "
      "#0626d6 #5c0a08 #e3f92f #49ff00 #3ed78e "
      "#872cde #df5146 #b3b3b3 #b1b1b1 #afafaf "
      "#aeaeae #acacac #ababab #a9a9a9 #a8a8a8 "
      "#a6a6a6 #a4a4a4 #a3a3a3 #a1a1a1 #a0a0a0 "
      "#9e9e9e #9d9d9d #9b9b9b #9a9a9a #989898 "
      "#969696 #959595 #939393 #929292 #909090 "
      "#8f8f8f #8d8d8d #8b8b8b #8a8a8a #888888 "
      "#878787 #858585 #848484 #828282 #818181 "
      "#7f7f7f #7d7d7d #7c7c7c #7a7a7a #797979 "
      "#777777 #767676 #747474 #727272 #717171 "
      "#6f6f6f #6e6e6e #6c6c6c #6b6b6b #696969 "
      "#686868 #666666 #646464 #636363 #616161 "
      "#606060 #5e5e5e #5d5d5d #5b5b5b #5a5a5a "
      "#585858 #565656 #555555 #535353 #525252 "
      "#505050 #4f4f4f #4d4d4d #4b4b4b #4a4a4a "
      "#484848 #474747 #454545 #444444 #424242 "
      "#414141 #3f3f3f #3d3d3d #3c3c3c #3a3a3a "
      "#393939 #373737 #363636 #343434 #323232 "
      "#313131 #2f2f2f #2e2e2e #2c2c2c #2b2b2b "
      "#292929 #282828 #262626 #242424 #232323 "
      "#212121 #202020 #1e1e1e #1d1d1d #1b1b1b "
      "#1a1a1a "
};
static char CYTOARCH_ROI_256_GAP_CMD[] = {  
      "CytoArch_ROI_256_gap "
      "#84392e #018f67 #776b1b #01d9d4 #9f35b8 "
      "#f7d202 #2100cf #d494f6 #bbfa2d #fd2d74 "
      "#90c648 #c4516e #fe28fd #a83d26 #4fda69 "
      "#40fcf8 #c4589f #27abf3 #610051 #49f8c0 "
      "#ad185d #68f88d #d80491 #d92918 #2b649d "
      "#65bbea #772e83 #fed039 #0591b2 #ed2b3e "
      "#67a84b #cb7941 #7a2eb0 #39af94 #57fa28 "
      "#fb7dfd #a46b42 #13e94c #4b70f0 #c8cf33 "
      "#02e79a #fcae11 #96d7fb #42358b #0009fd "
      "#ff2bcf #9d9909 #173472 #fe7c31 #3780c8 "
      "#1041fe #f0d260 #a19349 #45ff8a #fd9376 "
      "#cf3fcc #c3c866 #059489 #3cfe59 #ff0091 "
      "#fbb3a1 #c8f104 #d92a70 #86ef42 #7b02ea "
      "#fde693 #b408b2 #1b52d4 #f687cd #8257b9 "
      "#88100b #fa03cb #e85783 #045602 #7d97fa "
      "#8cfe76 #1608a9 #fdff01 #ff56b9 #0d359a "
      "#b41335 #7b07ab #3dc0c5 #feab3d #6fc9af "
      "#0afdf9 #b9f760 #4cc50f #c067fe #fffb5f "
      "#df7e05 #ba00de #3d954b #c636f6 #05b7c2 "
      "#ac3d02 #0d7e3d #534fb4 #ac7119 #ab0a85 "
      "#0667a5 #17b80f #494be9 #860b3b #85c323 "
      "#6ddedd #3d888c #d5956d #378307 #390872 "
      "#8463ff #24f0c6 #d1b100 #02fc73 #90ffa8 "
      "#01c6fc #fd1017 #4407f2 #9b4450 #03b24b "
      "#a0428e #02bf89 #4d96ff #79490c #461ab6 "
      "#43d344 #b06dc9 #df4e04 #83d16f #04f025 "
      "#a2fee4 #e80153 #ffa6f8 #96f718 #5e83c0 "
      "#eb02f9 #bf0005 #cfa736 #0a7fdf #f685a0 "
      "#000a7a #e12ba0 #046372 #d1eb91 #740377 "
      "#39d6fc #708e1f #acb0fd #fd52fa #01840a "
      "#0626d6 #5c0a08 #e3f92f #49ff00 #3ed78e "
      "#872cde #df5146 #000000 #000000 #000000 "
      "#000000 #000000 #000000 #000000 #000000 "
      "#000000 #000000 #000000 #000000 #000000 "
      "#000000 #000000 #000000 #000000 #000000 "
      "#000000 #000000 #000000 #000000 #000000 "
      "#000000 #000000 #000000 #000000 #000000 "
      "#000000 #000000 #000000 #000000 #000000 "
      "#000000 #000000 #000000 #000000 #000000 "
      "#000000 #000000 #000000 #000000 #000000 "
      "#000000 #000000 #000000 #000000 #000000 "
      "#000000 #000000 #000000 #000000 #000000 "
      "#000000 #000000 #000000 #000000 #000000 "
      "#000000 #000000 #000000 #000000 #000000 "
      "#000000 #000000 #000000 #000000 #000000 "
      "#000000 #000000 #000000 #000000 #000000 "
      "#000000 #000000 #000000 #000000 #000000 "
      "#000000 #000000 #000000 #000000 #000000 "
      "#000000 #000000 #000000 #000000 #000000 "
      "#000000 #000000 #000000 #000000 #000000 "
      "#000000 #000000 #000000 #000000 #000000 "
      "#000000 "
};
/* While we're at it, some maps for ROI drawing 
   see matlab/MakeROIColMaps.m
*/
static char ROI_256_CMD[] = {  
      "ROI_256 "
      "#41a2b0 #0a32b6 #df70f8 #78f525 #d80475 "
      "#cf7c23 #fbb060 #5df345 #fc3820 #d97d98 "
      "#15b76c #fd8b14 #83b6ed #a544fa #adbd02 "
      "#8f0459 #90e18d #d90ad8 #56146f #59dffb "
      "#3f07d3 #fe2e95 #ac1f0a #01c12c #8ee1d6 "
      "#6bfa67 #2adb1f #4e29fb #dd0203 #086420 "
      "#de53fc #47b5f6 #7f2261 #7e9601 #a748db "
      "#21dfa7 #68a8c5 #02f804 #d05024 #d8fd74 "
      "#0007ce #fb7576 #07d66a #69022b #02f8cd "
      "#650acc #f80372 #be3b45 #fdb37f #3ea0cd "
      "#ff5a57 #e0f450 #a69229 #2504fb #6ecf91 "
      "#8a04cc #2d7dfd #22ffa1 #0660f7 #256401 "
      "#450195 #c9d009 #2b822b #7a33fd #c77461 "
      "#25b548 #adec88 #c235a1 #67f4ab #d305b5 "
      "#4ba51a #9f1cff #60b56c #045650 #ef60da "
      "#622ad6 #6efee7 #c101ff #fd8654 #a6c21f "
      "#28d66d #ff5c04 #3029da #82cc03 #8c89d9 "
      "#f35624 #65cf44 #090355 #b18ff1 #dc0327 "
      "#8564dd #20ef02 #04a4f0 #515e02 #3041ad "
      "#30fb2a #d283ce #6df405 #3cad6e #84392e "
      "#018f67 #776b1b #01d9d4 #9f35b8 #f7d202 "
      "#2100cf #d494f6 #bbfa2d #fd2d74 #90c648 "
      "#c4516e #fe28fd #a83d26 #4fda69 #40fcf8 "
      "#c4589f #27abf3 #610051 #49f8c0 #ad185d "
      "#68f88d #d80491 #d92918 #2b649d #65bbea "
      "#772e83 #fed039 #0591b2 #ed2b3e #67a84b "
      "#cb7941 #7a2eb0 #39af94 #57fa28 #fb7dfd "
      "#a46b42 #13e94c #4b70f0 #c8cf33 #02e79a "
      "#fcae11 #96d7fb #42358b #0009fd #ff2bcf "
      "#9d9909 #173472 #fe7c31 #3780c8 #1041fe "
      "#f0d260 #a19349 #45ff8a #fd9376 #cf3fcc "
      "#c3c866 #059489 #3cfe59 #ff0091 #fbb3a1 "
      "#c8f104 #d92a70 #86ef42 #7b02ea #fde693 "
      "#b408b2 #1b52d4 #f687cd #8257b9 #88100b "
      "#fa03cb #e85783 #045602 #7d97fa #8cfe76 "
      "#1608a9 #fdff01 #ff56b9 #0d359a #b41335 "
      "#7b07ab #3dc0c5 #feab3d #6fc9af #0afdf9 "
      "#b9f760 #4cc50f #c067fe #fffb5f #df7e05 "
      "#ba00de #3d954b #c636f6 #05b7c2 #ac3d02 "
      "#0d7e3d #534fb4 #ac7119 #ab0a85 #0667a5 "
      "#17b80f #494be9 #860b3b #85c323 #6ddedd "
      "#3d888c #d5956d #378307 #390872 #8463ff "
      "#24f0c6 #d1b100 #02fc73 #90ffa8 #01c6fc "
      "#fd1017 #4407f2 #9b4450 #03b24b #a0428e "
      "#02bf89 #4d96ff #79490c #461ab6 #43d344 "
      "#b06dc9 #df4e04 #83d16f #04f025 #a2fee4 "
      "#e80153 #ffa6f8 #96f718 #5e83c0 #eb02f9 "
      "#bf0005 #cfa736 #0a7fdf #f685a0 #000a7a "
      "#e12ba0 #046372 #d1eb91 #740377 #39d6fc "
      "#708e1f #acb0fd #fd52fa #01840a #0626d6 "
      "#5c0a08 #e3f92f #49ff00 #3ed78e #872cde "
      "#df5146 "
};
static char ROI_128_CMD[] = {  
      "ROI_128 "
      "#ed2b3e #ed2b3e #67a84b #67a84b #cb7941 "
      "#cb7941 #7a2eb0 #7a2eb0 #39af94 #39af94 "
      "#57fa28 #57fa28 #fb7dfd #fb7dfd #a46b42 "
      "#a46b42 #13e94c #13e94c #4b70f0 #4b70f0 "
      "#c8cf33 #c8cf33 #02e79a #02e79a #fcae11 "
      "#fcae11 #96d7fb #96d7fb #42358b #42358b "
      "#0009fd #0009fd #ff2bcf #ff2bcf #9d9909 "
      "#9d9909 #173472 #173472 #fe7c31 #fe7c31 "
      "#3780c8 #3780c8 #1041fe #1041fe #f0d260 "
      "#f0d260 #a19349 #a19349 #45ff8a #45ff8a "
      "#fd9376 #fd9376 #cf3fcc #cf3fcc #c3c866 "
      "#c3c866 #059489 #059489 #3cfe59 #3cfe59 "
      "#ff0091 #ff0091 #fbb3a1 #fbb3a1 #c8f104 "
      "#c8f104 #d92a70 #d92a70 #86ef42 #86ef42 "
      "#7b02ea #7b02ea #fde693 #fde693 #b408b2 "
      "#b408b2 #1b52d4 #1b52d4 #f687cd #f687cd "
      "#8257b9 #8257b9 #88100b #88100b #fa03cb "
      "#fa03cb #e85783 #e85783 #045602 #045602 "
      "#7d97fa #7d97fa #8cfe76 #8cfe76 #1608a9 "
      "#1608a9 #fdff01 #fdff01 #ff56b9 #ff56b9 "
      "#0d359a #0d359a #b41335 #b41335 #7b07ab "
      "#7b07ab #3dc0c5 #3dc0c5 #feab3d #feab3d "
      "#6fc9af #6fc9af #0afdf9 #0afdf9 #b9f760 "
      "#b9f760 #4cc50f #4cc50f #c067fe #c067fe "
      "#fffb5f #fffb5f #df7e05 #df7e05 #ba00de "
      "#ba00de #3d954b #3d954b #c636f6 #c636f6 "
      "#05b7c2 #05b7c2 #ac3d02 #ac3d02 #0d7e3d "
      "#0d7e3d #534fb4 #534fb4 #ac7119 #ac7119 "
      "#ab0a85 #ab0a85 #0667a5 #0667a5 #17b80f "
      "#17b80f #494be9 #494be9 #860b3b #860b3b "
      "#85c323 #85c323 #6ddedd #6ddedd #3d888c "
      "#3d888c #d5956d #d5956d #378307 #378307 "
      "#390872 #390872 #8463ff #8463ff #24f0c6 "
      "#24f0c6 #d1b100 #d1b100 #02fc73 #02fc73 "
      "#90ffa8 #90ffa8 #01c6fc #01c6fc #fd1017 "
      "#fd1017 #4407f2 #4407f2 #9b4450 #9b4450 "
      "#03b24b #03b24b #a0428e #a0428e #02bf89 "
      "#02bf89 #4d96ff #4d96ff #79490c #79490c "
      "#461ab6 #461ab6 #43d344 #43d344 #b06dc9 "
      "#b06dc9 #df4e04 #df4e04 #83d16f #83d16f "
      "#04f025 #04f025 #a2fee4 #a2fee4 #e80153 "
      "#e80153 #ffa6f8 #ffa6f8 #96f718 #96f718 "
      "#5e83c0 #5e83c0 #eb02f9 #eb02f9 #bf0005 "
      "#bf0005 #cfa736 #cfa736 #0a7fdf #0a7fdf "
      "#f685a0 #f685a0 #000a7a #000a7a #e12ba0 "
      "#e12ba0 #046372 #046372 #d1eb91 #d1eb91 "
      "#740377 #740377 #39d6fc #39d6fc #708e1f "
      "#708e1f #acb0fd #acb0fd #fd52fa #fd52fa "
      "#01840a #01840a #0626d6 #0626d6 #5c0a08 "
      "#5c0a08 #e3f92f #e3f92f #49ff00 #49ff00 "
      "#3ed78e #3ed78e #872cde #872cde #df5146 "
      "#df5146 "
};
static char ROI_64_CMD[] = {  
      "ROI_64 "
      "#c636f6 #c636f6 #c636f6 #c636f6 #05b7c2 "
      "#05b7c2 #05b7c2 #05b7c2 #ac3d02 #ac3d02 "
      "#ac3d02 #ac3d02 #0d7e3d #0d7e3d #0d7e3d "
      "#0d7e3d #534fb4 #534fb4 #534fb4 #534fb4 "
      "#ac7119 #ac7119 #ac7119 #ac7119 #ab0a85 "
      "#ab0a85 #ab0a85 #ab0a85 #0667a5 #0667a5 "
      "#0667a5 #0667a5 #17b80f #17b80f #17b80f "
      "#17b80f #494be9 #494be9 #494be9 #494be9 "
      "#860b3b #860b3b #860b3b #860b3b #85c323 "
      "#85c323 #85c323 #85c323 #6ddedd #6ddedd "
      "#6ddedd #6ddedd #3d888c #3d888c #3d888c "
      "#3d888c #d5956d #d5956d #d5956d #d5956d "
      "#378307 #378307 #378307 #378307 #390872 "
      "#390872 #390872 #390872 #8463ff #8463ff "
      "#8463ff #8463ff #24f0c6 #24f0c6 #24f0c6 "
      "#24f0c6 #d1b100 #d1b100 #d1b100 #d1b100 "
      "#02fc73 #02fc73 #02fc73 #02fc73 #90ffa8 "
      "#90ffa8 #90ffa8 #90ffa8 #01c6fc #01c6fc "
      "#01c6fc #01c6fc #fd1017 #fd1017 #fd1017 "
      "#fd1017 #4407f2 #4407f2 #4407f2 #4407f2 "
      "#9b4450 #9b4450 #9b4450 #9b4450 #03b24b "
      "#03b24b #03b24b #03b24b #a0428e #a0428e "
      "#a0428e #a0428e #02bf89 #02bf89 #02bf89 "
      "#02bf89 #4d96ff #4d96ff #4d96ff #4d96ff "
      "#79490c #79490c #79490c #79490c #461ab6 "
      "#461ab6 #461ab6 #461ab6 #43d344 #43d344 "
      "#43d344 #43d344 #b06dc9 #b06dc9 #b06dc9 "
      "#b06dc9 #df4e04 #df4e04 #df4e04 #df4e04 "
      "#83d16f #83d16f #83d16f #83d16f #04f025 "
      "#04f025 #04f025 #04f025 #a2fee4 #a2fee4 "
      "#a2fee4 #a2fee4 #e80153 #e80153 #e80153 "
      "#e80153 #ffa6f8 #ffa6f8 #ffa6f8 #ffa6f8 "
      "#96f718 #96f718 #96f718 #96f718 #5e83c0 "
      "#5e83c0 #5e83c0 #5e83c0 #eb02f9 #eb02f9 "
      "#eb02f9 #eb02f9 #bf0005 #bf0005 #bf0005 "
      "#bf0005 #cfa736 #cfa736 #cfa736 #cfa736 "
      "#0a7fdf #0a7fdf #0a7fdf #0a7fdf #f685a0 "
      "#f685a0 #f685a0 #f685a0 #000a7a #000a7a "
      "#000a7a #000a7a #e12ba0 #e12ba0 #e12ba0 "
      "#e12ba0 #046372 #046372 #046372 #046372 "
      "#d1eb91 #d1eb91 #d1eb91 #d1eb91 #740377 "
      "#740377 #740377 #740377 #39d6fc #39d6fc "
      "#39d6fc #39d6fc #708e1f #708e1f #708e1f "
      "#708e1f #acb0fd #acb0fd #acb0fd #acb0fd "
      "#fd52fa #fd52fa #fd52fa #fd52fa #01840a "
      "#01840a #01840a #01840a #0626d6 #0626d6 "
      "#0626d6 #0626d6 #5c0a08 #5c0a08 #5c0a08 "
      "#5c0a08 #e3f92f #e3f92f #e3f92f #e3f92f "
      "#49ff00 #49ff00 #49ff00 #49ff00 #3ed78e "
      "#3ed78e #3ed78e #3ed78e #872cde #872cde "
      "#872cde #872cde #df5146 #df5146 #df5146 "
      "#df5146 "
};

static char ROI_32_CMD[] = {  
      "ROI_32 "
      "#43d344 #43d344 #43d344 #43d344 #43d344 "
      "#43d344 #43d344 #43d344 #b06dc9 #b06dc9 "
      "#b06dc9 #b06dc9 #b06dc9 #b06dc9 #b06dc9 "
      "#b06dc9 #df4e04 #df4e04 #df4e04 #df4e04 "
      "#df4e04 #df4e04 #df4e04 #df4e04 #83d16f "
      "#83d16f #83d16f #83d16f #83d16f #83d16f "
      "#83d16f #83d16f #04f025 #04f025 #04f025 "
      "#04f025 #04f025 #04f025 #04f025 #04f025 "
      "#a2fee4 #a2fee4 #a2fee4 #a2fee4 #a2fee4 "
      "#a2fee4 #a2fee4 #a2fee4 #e80153 #e80153 "
      "#e80153 #e80153 #e80153 #e80153 #e80153 "
      "#e80153 #ffa6f8 #ffa6f8 #ffa6f8 #ffa6f8 "
      "#ffa6f8 #ffa6f8 #ffa6f8 #ffa6f8 #96f718 "
      "#96f718 #96f718 #96f718 #96f718 #96f718 "
      "#96f718 #96f718 #5e83c0 #5e83c0 #5e83c0 "
      "#5e83c0 #5e83c0 #5e83c0 #5e83c0 #5e83c0 "
      "#eb02f9 #eb02f9 #eb02f9 #eb02f9 #eb02f9 "
      "#eb02f9 #eb02f9 #eb02f9 #bf0005 #bf0005 "
      "#bf0005 #bf0005 #bf0005 #bf0005 #bf0005 "
      "#bf0005 #cfa736 #cfa736 #cfa736 #cfa736 "
      "#cfa736 #cfa736 #cfa736 #cfa736 #0a7fdf "
      "#0a7fdf #0a7fdf #0a7fdf #0a7fdf #0a7fdf "
      "#0a7fdf #0a7fdf #f685a0 #f685a0 #f685a0 "
      "#f685a0 #f685a0 #f685a0 #f685a0 #f685a0 "
      "#000a7a #000a7a #000a7a #000a7a #000a7a "
      "#000a7a #000a7a #000a7a #e12ba0 #e12ba0 "
      "#e12ba0 #e12ba0 #e12ba0 #e12ba0 #e12ba0 "
      "#e12ba0 #046372 #046372 #046372 #046372 "
      "#046372 #046372 #046372 #046372 #d1eb91 "
      "#d1eb91 #d1eb91 #d1eb91 #d1eb91 #d1eb91 "
      "#d1eb91 #d1eb91 #740377 #740377 #740377 "
      "#740377 #740377 #740377 #740377 #740377 "
      "#39d6fc #39d6fc #39d6fc #39d6fc #39d6fc "
      "#39d6fc #39d6fc #39d6fc #708e1f #708e1f "
      "#708e1f #708e1f #708e1f #708e1f #708e1f "
      "#708e1f #acb0fd #acb0fd #acb0fd #acb0fd "
      "#acb0fd #acb0fd #acb0fd #acb0fd #fd52fa "
      "#fd52fa #fd52fa #fd52fa #fd52fa #fd52fa "
      "#fd52fa #fd52fa #01840a #01840a #01840a "
      "#01840a #01840a #01840a #01840a #01840a "
      "#0626d6 #0626d6 #0626d6 #0626d6 #0626d6 "
      "#0626d6 #0626d6 #0626d6 #5c0a08 #5c0a08 "
      "#5c0a08 #5c0a08 #5c0a08 #5c0a08 #5c0a08 "
      "#5c0a08 #e3f92f #e3f92f #e3f92f #e3f92f "
      "#e3f92f #e3f92f #e3f92f #e3f92f #49ff00 "
      "#49ff00 #49ff00 #49ff00 #49ff00 #49ff00 "
      "#49ff00 #49ff00 #3ed78e #3ed78e #3ed78e "
      "#3ed78e #3ed78e #3ed78e #3ed78e #3ed78e "
      "#872cde #872cde #872cde #872cde #872cde "
      "#872cde #872cde #872cde #df5146 #df5146 "
      "#df5146 #df5146 #df5146 #df5146 #df5146 "
      "#df5146 "
};

/* Some maps for color blindness
Thanks to Vince Hradil who created them
based on http://bsp.pdx.edu/Publications/2006/SPM_McNames.pdf
*/
static char CB_CS_35[] = {  
      "cb_spiral35  "
      "#c776ee #c776ee #c776ee #be75f1 "
      "#be75f1 #b574f5 #b574f5 #ac75f8 "
      "#ac75f8 #a276fb #a276fb #9878fd "
      "#9878fd #9878fd #8d7bfe #8d7bfe "
      "#837eff #837eff #7983ff #7983ff "
      "#6f88fe #6f88fe #658efc #658efc "
      "#658efc #5b94f9 #5b94f9 #529bf5 "
      "#529bf5 #4aa2f0 #4aa2f0 #42aaea "
      "#42aaea #3bb2e3 #3bb2e3 #3bb2e3 "
      "#34badb #34badb #2fc2d3 #2fc2d3 "
      "#2bcac9 #2bcac9 #27d2be #27d2be "
      "#25dab3 #25dab3 #24e1a7 #24e1a7 "
      "#24e1a7 #24e79a #24e79a #26ed8d "
      "#26ed8d #28f27f #28f27f #2cf672 "
      "#2cf672 #31f964 #31f964 #31f964 "
      "#37fa56 #37fa56 #3ffa49 #3ffa49 "
      "#47f83d #47f83d #50f431 #50f431 "
      "#5aef27 #5aef27 #5aef27 #64e81e "
      "#64e81e #6de016 #6de016 #77d70f "
      "#77d70f #80cd0a #80cd0a #89c306 "
      "#89c306 #89c306 #91b803 #91b803 "
      "#98ac01 #98ac01 #9fa000 #9fa000 "
      "#a49401 #a49401 #a98802 #a98802 "
      "#ad7c04 #ad7c04 #ad7c04 #b07007 "
      "#b07007 #b2640b #b2640b #b35810 "
      "#b35810 #b24d15 #b24d15 #b1431a "
      "#b1431a #b1431a #af3920 #af3920 "
      "#ac3026 #ac3026 #a8282c #a8282c "
      "#a42033 #a42033 #9e1939 #9e1939 "
      "#9e1939 #98133f #98133f #910e45 "
      "#910e45 #8a0a4a #8a0a4a #830650 "
      "#830650 #7b0354 #7b0354 #7b0354 "
}; 

static char CB_CS[] = {  
      "cb_spiral "
      "#ffffff #fdfffc #fafff9 #f8fff5 "
      "#f6fff1 #f5feed #f4fde9 #f4fce4 "
      "#f4fbe0 #f4f9db #f4f6d7 #f5f4d3 "
      "#f6f0cf #f7edcc #f9e8c9 #fae4c6 "
      "#fbdfc4 #fdd9c2 #fed4c0 #ffcec0 "
      "#ffc7bf #ffc1bf #ffbac0 #ffb3c2 "
      "#fdacc4 #fca6c6 #f99fc9 #f799cc "
      "#f393d0 #ef8dd4 #ea88d8 #e483dc "
      "#de7fe0 #d77be5 #cf78e9 #c776ee "
      "#be75f1 #b574f5 #ac75f8 #a276fb "
      "#9878fd #8d7bfe #837eff #7983ff "
      "#6f88fe #658efc #5b94f9 #529bf5 "
      "#4aa2f0 #42aaea #3bb2e3 #34badb "
      "#2fc2d3 #2bcac9 #27d2be #25dab3 "
      "#24e1a7 #24e79a #26ed8d #28f27f "
      "#2cf672 #31f964 #37fa56 #3ffa49 "
      "#47f83d #50f431 #5aef27 #64e81e "
      "#6de016 #77d70f #80cd0a #89c306 "
      "#91b803 #98ac01 #9fa000 #a49401 "
      "#a98802 #ad7c04 #b07007 #b2640b "
      "#b35810 #b24d15 #b1431a #af3920 "
      "#ac3026 #a8282c #a42033 #9e1939 "
      "#98133f #910e45 #8a0a4a #830650 "
      "#7b0354 #720158 #6a005c #62005f "
      "#590061 #510163 #480264 #400464 "
      "#390663 #320862 #2b0a61 #240d5e "
      "#1e105b #191358 #141554 #101850 "
      "#0c1a4b #091c46 #061e41 #041f3c "
      "#022036 #012131 #00212c #002127 "
      "#002022 #001f1d #001d18 #001b14 "
      "#001810 #01160c #011209 #010f07 "
      "#010b04 #010702 #000401 #010101 "
};  /* changed last index to non-zero - not transparent */

/* regular gray from white to black */
static char GRAY_CS[] = {
   "gray_scale "
   "#ffffff #eeeeee #dddddd #cccccc "
   "#bbbbbb #aaaaaa #999999 #888888 "
   "#777777 #666666 #555555 #444444 "
   "#333333 #222222 #111111 #010101 "
};

/* mirrored gray for +/- values */
static char GRAY_CIRCLE_CS[] = {
   "gray_circle "
   "#ffffff #eeeeee #dddddd #cccccc "
   "#bbbbbb #aaaaaa #999999 #888888 "
   "#777777 #666666 #555555 #444444 "
   "#333333 #222222 #111111 #010101 "
   "#111111 #222222 #333333 #444444 "
   "#555555 #666666 #777777 #888888 "
   "#999999 #aaaaaa #bbbbbb #cccccc "
   "#dddddd #eeeeee #ffffff "
};
/* mirrored and inverted gray for +/- values */
static char GRAY_INV_CIRCLE_CS[] = {
   "inverted_gray_circle "
   "#010101 "
   "#111111 #222222 #333333 #444444 "
   "#555555 #666666 #777777 #888888 "
   "#999999 #aaaaaa #bbbbbb #cccccc "
   "#dddddd #eeeeee #ffffff "
   "#eeeeee #dddddd #cccccc "
   "#bbbbbb #aaaaaa #999999 #888888 "
   "#777777 #666666 #555555 #444444 "
   "#333333 #222222 #111111 #010101 "
};
