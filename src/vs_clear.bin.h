static const uint8_t vs_clear_glsl[164] =
{
	0x56, 0x53, 0x48, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x95, 0x00, 0x00, 0x00, 0x61, 0x74, // VSH...........at
	0x74, 0x72, 0x69, 0x62, 0x75, 0x74, 0x65, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, 0x76, 0x65, // tribute highp ve
	0x63, 0x33, 0x20, 0x61, 0x5f, 0x70, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x3b, 0x0a, 0x76, // c3 a_position;.v
	0x6f, 0x69, 0x64, 0x20, 0x6d, 0x61, 0x69, 0x6e, 0x20, 0x28, 0x29, 0x0a, 0x7b, 0x0a, 0x20, 0x20, // oid main ().{.  
	0x68, 0x69, 0x67, 0x68, 0x70, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, // highp vec4 tmpva
	0x72, 0x5f, 0x31, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x2e, // r_1;.  tmpvar_1.
	0x77, 0x20, 0x3d, 0x20, 0x31, 0x2e, 0x30, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, // w = 1.0;.  tmpva
	0x72, 0x5f, 0x31, 0x2e, 0x78, 0x79, 0x7a, 0x20, 0x3d, 0x20, 0x61, 0x5f, 0x70, 0x6f, 0x73, 0x69, // r_1.xyz = a_posi
	0x74, 0x69, 0x6f, 0x6e, 0x3b, 0x0a, 0x20, 0x20, 0x67, 0x6c, 0x5f, 0x50, 0x6f, 0x73, 0x69, 0x74, // tion;.  gl_Posit
	0x69, 0x6f, 0x6e, 0x20, 0x3d, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x3b, 0x0a, // ion = tmpvar_1;.
	0x7d, 0x0a, 0x0a, 0x00,                                                                         // }...
};

#if 0
static const uint8_t vs_clear_glsl[] = {
 0x56, 0x53, 0x48, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x01, 0x00, 0x00,
 0x00, 0x03, 0xe7, 0x04, 0xb0, 0xb0, 0xca, 0xea, 0x6f, 0xc2, 0x0b, 0x41, 0x00, 0x01, 0x00, 0x00,  //..ç.°°ÊêoÂ.A....
 0xa8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //¨...............
 0x00, 0x00, 0x00, 0x00, 0x53, 0x68, 0x64, 0x72, 0x07, 0x00, 0x01, 0x00, 0x01, 0x0d, 0x00, 0x00,  //....Shdr........
 0x00, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00,  //....d.......4...
 0xff, 0xff, 0xff, 0xff, 0x41, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //ÿÿÿÿA...........
 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00,  //................
 0x17, 0x00, 0x02, 0x10, 0x00, 0x04, 0x03, 0x00, 0xff, 0x03, 0xeb, 0xbe, 0x08, 0x00, 0x00, 0x00,  //........,ÿ.ë¾....
 0x00, 0x21, 0x80, 0xbe, 0xf2, 0x02, 0x00, 0x7e, 0xcf, 0x08, 0x00, 0xf8, 0x04, 0x05, 0x06, 0x00,  //.!.¾,ò..~Ï..ø....
 0x0f, 0x02, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0xbf, 0x39, 0x6a, 0x06, 0x00,  //...,ø.......¿9j..
 0x04, 0x00, 0x00, 0x5b, 0x00, 0x01, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,  //...[............,
 0x12, 0x00, 0x00, 0x00, 0x17, 0x00, 0x02, 0x10, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //................,
 0x4f, 0x72, 0x62, 0x53, 0x68, 0x64, 0x72, 0x07, 0x47, 0x24, 0x00, 0x00, 0x02, 0x02, 0x0c, 0x00,  //,OrbShdr.G$......
 0xb0, 0xb0, 0xca, 0xea, 0x6f, 0xc2, 0x0b, 0x41, 0xe4, 0x72, 0xb4, 0x1f, 0x00, 0x00, 0x00, 0x00,  //°°,ÊêoÂ.Aär´.....
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00,  //................,
 0x00, 0x00, 0x00, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x02, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //....,....$......,
 0x18, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x03, 0x2e, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,  //................,
 0x1e, 0x00, 0x00, 0x00, 0x26, 0x00, 0x00, 0x00, 0x61, 0x5f, 0x70, 0x6f, 0x73, 0x69, 0x74, 0x69,  //....&...,a_positi
 0x6f, 0x6e, 0x00, 0x41, 0x5f, 0x50, 0x4f, 0x53, 0x49, 0x54, 0x49, 0x4f, 0x4e, 0x00, 0x67, 0x6c,  //,on.A_POSITION.gl
 0x5f, 0x50, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x00, 0x28, 0x6e, 0x6f, 0x5f, 0x6e, 0x61,  //_Position.(no_na
 0x6d, 0x65, 0x29, 0x00                                                                           //me).
};

const uint32_t vs_clear_glsl_size = sizeof(vs_clear_glsl);
#endif

static const uint8_t vs_clear_spv[568] =
{
	0x56, 0x53, 0x48, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x02, 0x00, 0x00, 0x03, 0x02, // VSH.......$.....
	0x23, 0x07, 0x00, 0x00, 0x01, 0x00, 0x06, 0x00, 0x08, 0x00, 0x4f, 0x00, 0x00, 0x00, 0x00, 0x00, // #.........O.....
	0x00, 0x00, 0x11, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x06, 0x00, 0x01, 0x00, // ................
	0x00, 0x00, 0x47, 0x4c, 0x53, 0x4c, 0x2e, 0x73, 0x74, 0x64, 0x2e, 0x34, 0x35, 0x30, 0x00, 0x00, // ..GLSL.std.450..
	0x00, 0x00, 0x0e, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0f, 0x00, // ................
	0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x6d, 0x61, 0x69, 0x6e, 0x00, 0x00, // ..........main..
	0x00, 0x00, 0x27, 0x00, 0x00, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00, 0x05, 0x00, // ..'...*.........
	0x00, 0x00, 0xf4, 0x01, 0x00, 0x00, 0x05, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0x6d, 0x61, // ..............ma
	0x69, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x05, 0x00, 0x27, 0x00, 0x00, 0x00, 0x61, 0x5f, // in........'...a_
	0x70, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x00, 0x00, 0x05, 0x00, 0x0a, 0x00, 0x2a, 0x00, // position......*.
	0x00, 0x00, 0x40, 0x65, 0x6e, 0x74, 0x72, 0x79, 0x50, 0x6f, 0x69, 0x6e, 0x74, 0x4f, 0x75, 0x74, // ..@entryPointOut
	0x70, 0x75, 0x74, 0x2e, 0x67, 0x6c, 0x5f, 0x50, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x00, // put.gl_Position.
	0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x27, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, // ..G...'.........
	0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, // ..G...*.........
	0x00, 0x00, 0x13, 0x00, 0x02, 0x00, 0x02, 0x00, 0x00, 0x00, 0x21, 0x00, 0x03, 0x00, 0x03, 0x00, // ..........!.....
	0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x16, 0x00, 0x03, 0x00, 0x06, 0x00, 0x00, 0x00, 0x20, 0x00, // .............. .
	0x00, 0x00, 0x17, 0x00, 0x04, 0x00, 0x07, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x03, 0x00, // ................
	0x00, 0x00, 0x17, 0x00, 0x04, 0x00, 0x09, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x04, 0x00, // ................
	0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, // ..+.............
	0x80, 0x3f, 0x20, 0x00, 0x04, 0x00, 0x26, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x07, 0x00, // .? ...&.........
	0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x26, 0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00, 0x01, 0x00, // ..;...&...'.....
	0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x29, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x09, 0x00, // .. ...).........
	0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x29, 0x00, 0x00, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x03, 0x00, // ..;...)...*.....
	0x00, 0x00, 0x36, 0x00, 0x05, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, // ..6.............
	0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x02, 0x00, 0x05, 0x00, 0x00, 0x00, 0x3d, 0x00, // ..............=.
	0x04, 0x00, 0x07, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00, 0x51, 0x00, // ......(...'...Q.
	0x05, 0x00, 0x06, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, // ......8...(.....
	0x00, 0x00, 0x51, 0x00, 0x05, 0x00, 0x06, 0x00, 0x00, 0x00, 0x39, 0x00, 0x00, 0x00, 0x28, 0x00, // ..Q.......9...(.
	0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x51, 0x00, 0x05, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3a, 0x00, // ......Q.......:.
	0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x50, 0x00, 0x07, 0x00, 0x09, 0x00, // ..(.......P.....
	0x00, 0x00, 0x3b, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x39, 0x00, 0x00, 0x00, 0x3a, 0x00, // ..;...8...9...:.
	0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f, 0x00, // ..............?.
	0x00, 0x00, 0x39, 0x00, 0x00, 0x00, 0x52, 0x00, 0x06, 0x00, 0x09, 0x00, 0x00, 0x00, 0x4e, 0x00, // ..9...R.......N.
	0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x3e, 0x00, // ..?...;.......>.
	0x03, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x4e, 0x00, 0x00, 0x00, 0xfd, 0x00, 0x01, 0x00, 0x38, 0x00, // ..*...N.......8.
	0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00,                                                 // ........
};
static const uint8_t vs_clear_dx9[175] =
{
	0x56, 0x53, 0x48, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x03, // VSH.............
	0xfe, 0xff, 0xfe, 0xff, 0x14, 0x00, 0x43, 0x54, 0x41, 0x42, 0x1c, 0x00, 0x00, 0x00, 0x23, 0x00, // ......CTAB....#.
	0x00, 0x00, 0x00, 0x03, 0xfe, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x91, // ................
	0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x76, 0x73, 0x5f, 0x33, 0x5f, 0x30, 0x00, 0x4d, 0x69, 0x63, // ......vs_3_0.Mic
	0x72, 0x6f, 0x73, 0x6f, 0x66, 0x74, 0x20, 0x28, 0x52, 0x29, 0x20, 0x48, 0x4c, 0x53, 0x4c, 0x20, // rosoft (R) HLSL 
	0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x20, 0x43, 0x6f, 0x6d, 0x70, 0x69, 0x6c, 0x65, 0x72, 0x20, // Shader Compiler 
	0x31, 0x30, 0x2e, 0x31, 0x00, 0xab, 0x51, 0x00, 0x00, 0x05, 0x00, 0x00, 0x0f, 0xa0, 0x00, 0x00, // 10.1..Q.........
	0x80, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, // .?..............
	0x00, 0x02, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x0f, 0x90, 0x1f, 0x00, 0x00, 0x02, 0x00, 0x00, // ................
	0x00, 0x80, 0x00, 0x00, 0x0f, 0xe0, 0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x0f, 0xe0, 0x00, 0x00, // ................
	0x24, 0x90, 0x00, 0x00, 0x40, 0xa0, 0x00, 0x00, 0x15, 0xa0, 0xff, 0xff, 0x00, 0x00, 0x00,       // $...@..........
};
static const uint8_t vs_clear_dx11[388] =
{
	0x56, 0x53, 0x48, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x01, 0x00, 0x00, 0x44, 0x58, // VSH.......p...DX
	0x42, 0x43, 0x35, 0x37, 0xf0, 0x90, 0x23, 0xc6, 0x3b, 0x7a, 0xd4, 0x66, 0x38, 0xf5, 0x51, 0x69, // BC57..#.;z.f8.Qi
	0x19, 0xa8, 0x01, 0x00, 0x00, 0x00, 0x70, 0x01, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x30, 0x00, // ......p.......0.
	0x00, 0x00, 0xb0, 0x00, 0x00, 0x00, 0x08, 0x01, 0x00, 0x00, 0x3c, 0x01, 0x00, 0x00, 0x41, 0x6f, // ..........<...Ao
	0x6e, 0x39, 0x78, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x02, 0xfe, 0xff, 0x50, 0x00, // n9x...x.......P.
	0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, // ..(.....$...$...
	0x24, 0x00, 0x00, 0x00, 0x24, 0x00, 0x01, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, // $...$...$.......
	0xfe, 0xff, 0x51, 0x00, 0x00, 0x05, 0x01, 0x00, 0x0f, 0xa0, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, // ..Q..........?..
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x02, 0x05, 0x00, // ................
	0x00, 0x80, 0x00, 0x00, 0x0f, 0x90, 0x02, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, // ................
	0xe4, 0x90, 0x00, 0x00, 0xe4, 0xa0, 0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x0c, 0xc0, 0x00, 0x00, // ................
	0xaa, 0x90, 0x01, 0x00, 0x44, 0xa0, 0x01, 0x00, 0x14, 0xa0, 0xff, 0xff, 0x00, 0x00, 0x53, 0x48, // ....D.........SH
	0x44, 0x52, 0x50, 0x00, 0x00, 0x00, 0x40, 0x00, 0x01, 0x00, 0x14, 0x00, 0x00, 0x00, 0x5f, 0x00, // DRP...@......._.
	0x00, 0x03, 0x72, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x67, 0x00, 0x00, 0x04, 0xf2, 0x20, // ..r.......g.... 
	0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x05, 0x72, 0x20, // ..........6...r 
	0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46, 0x12, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, // ......F.......6.
	0x00, 0x05, 0x82, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x00, 0x00, // ... .......@....
	0x80, 0x3f, 0x3e, 0x00, 0x00, 0x01, 0x49, 0x53, 0x47, 0x4e, 0x2c, 0x00, 0x00, 0x00, 0x01, 0x00, // .?>...ISGN,.....
	0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ...... .........
	0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x00, 0x00, 0x50, 0x4f, // ..............PO
	0x53, 0x49, 0x54, 0x49, 0x4f, 0x4e, 0x00, 0xab, 0xab, 0xab, 0x4f, 0x53, 0x47, 0x4e, 0x2c, 0x00, // SITION....OSGN,.
	0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, // .......... .....
	0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, // ................
	0x00, 0x00, 0x53, 0x56, 0x5f, 0x50, 0x4f, 0x53, 0x49, 0x54, 0x49, 0x4f, 0x4e, 0x00, 0x00, 0x01, // ..SV_POSITION...
	0x01, 0x00, 0x00, 0x00,                                                                         // ....
};
static const uint8_t vs_clear_mtl[504] =
{
	0x56, 0x53, 0x48, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe9, 0x01, 0x00, 0x00, 0x75, 0x73, // VSH...........us
	0x69, 0x6e, 0x67, 0x20, 0x6e, 0x61, 0x6d, 0x65, 0x73, 0x70, 0x61, 0x63, 0x65, 0x20, 0x6d, 0x65, // ing namespace me
	0x74, 0x61, 0x6c, 0x3b, 0x0a, 0x73, 0x74, 0x72, 0x75, 0x63, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, // tal;.struct xlat
	0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x49, 0x6e, 0x70, 0x75, 0x74, 0x20, 0x7b, // MtlShaderInput {
	0x0a, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x33, 0x20, 0x61, 0x5f, 0x70, 0x6f, 0x73, 0x69, // .  float3 a_posi
	0x74, 0x69, 0x6f, 0x6e, 0x20, 0x5b, 0x5b, 0x61, 0x74, 0x74, 0x72, 0x69, 0x62, 0x75, 0x74, 0x65, // tion [[attribute
	0x28, 0x30, 0x29, 0x5d, 0x5d, 0x3b, 0x0a, 0x7d, 0x3b, 0x0a, 0x73, 0x74, 0x72, 0x75, 0x63, 0x74, // (0)]];.};.struct
	0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x4f, 0x75, //  xlatMtlShaderOu
	0x74, 0x70, 0x75, 0x74, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, // tput {.  float4 
	0x67, 0x6c, 0x5f, 0x50, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x5b, 0x5b, 0x70, 0x6f, // gl_Position [[po
	0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x5d, 0x5d, 0x3b, 0x0a, 0x7d, 0x3b, 0x0a, 0x73, 0x74, 0x72, // sition]];.};.str
	0x75, 0x63, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, // uct xlatMtlShade
	0x72, 0x55, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x7b, 0x0a, 0x7d, 0x3b, 0x0a, 0x76, 0x65, // rUniform {.};.ve
	0x72, 0x74, 0x65, 0x78, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, // rtex xlatMtlShad
	0x65, 0x72, 0x4f, 0x75, 0x74, 0x70, 0x75, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, // erOutput xlatMtl
	0x4d, 0x61, 0x69, 0x6e, 0x20, 0x28, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, // Main (xlatMtlSha
	0x64, 0x65, 0x72, 0x49, 0x6e, 0x70, 0x75, 0x74, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x69, 0x20, // derInput _mtl_i 
	0x5b, 0x5b, 0x73, 0x74, 0x61, 0x67, 0x65, 0x5f, 0x69, 0x6e, 0x5d, 0x5d, 0x2c, 0x20, 0x63, 0x6f, // [[stage_in]], co
	0x6e, 0x73, 0x74, 0x61, 0x6e, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, // nstant xlatMtlSh
	0x61, 0x64, 0x65, 0x72, 0x55, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x26, 0x20, 0x5f, 0x6d, 0x74, // aderUniform& _mt
	0x6c, 0x5f, 0x75, 0x20, 0x5b, 0x5b, 0x62, 0x75, 0x66, 0x66, 0x65, 0x72, 0x28, 0x30, 0x29, 0x5d, // l_u [[buffer(0)]
	0x5d, 0x29, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, // ]).{.  xlatMtlSh
	0x61, 0x64, 0x65, 0x72, 0x4f, 0x75, 0x74, 0x70, 0x75, 0x74, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, // aderOutput _mtl_
	0x6f, 0x3b, 0x0a, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x74, 0x6d, 0x70, 0x76, // o;.  float4 tmpv
	0x61, 0x72, 0x5f, 0x31, 0x20, 0x3d, 0x20, 0x30, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, // ar_1 = 0;.  tmpv
	0x61, 0x72, 0x5f, 0x31, 0x2e, 0x77, 0x20, 0x3d, 0x20, 0x31, 0x2e, 0x30, 0x3b, 0x0a, 0x20, 0x20, // ar_1.w = 1.0;.  
	0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x2e, 0x78, 0x79, 0x7a, 0x20, 0x3d, 0x20, 0x5f, // tmpvar_1.xyz = _
	0x6d, 0x74, 0x6c, 0x5f, 0x69, 0x2e, 0x61, 0x5f, 0x70, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, // mtl_i.a_position
	0x3b, 0x0a, 0x20, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x6f, 0x2e, 0x67, 0x6c, 0x5f, 0x50, 0x6f, // ;.  _mtl_o.gl_Po
	0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x3d, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, // sition = tmpvar_
	0x31, 0x3b, 0x0a, 0x20, 0x20, 0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, 0x20, 0x5f, 0x6d, 0x74, 0x6c, // 1;.  return _mtl
	0x5f, 0x6f, 0x3b, 0x0a, 0x7d, 0x0a, 0x0a, 0x00,                                                 // _o;.}...
};

const uint8_t vs_clear_glsl_ps4[476] = {
	0x56, 0x53, 0x48, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x95, 0x00, 0x00, 0x00, 0x61, 0x74, 0x74, 0x72, 
	0x69, 0x62, 0x75, 0x74, 0x65, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 
	0x20, 0x76, 0x65, 0x63, 0x33, 0x20, 0x61, 0x5f, 0x70, 0x6f, 0x73, 
	0x69, 0x74, 0x69, 0x6f, 0x6e, 0x3b, 0x0a, 0x76, 0x6f, 0x69, 0x64, 
	0x20, 0x6d, 0x61, 0x69, 0x6e, 0x20, 0x28, 0x29, 0x0a, 0x7b, 0x0a, 
	0x20, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, 0x76, 0x65, 0x63, 
	0x34, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x3b, 
	0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 
	0x2e, 0x77, 0x20, 0x3d, 0x20, 0x31, 0x2e, 0x30, 0x3b, 0x0a, 0x20, 
	0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x2e, 0x78, 
	0x79, 0x7a, 0x20, 0x3d, 0x20, 0x61, 0x5f, 0x70, 0x6f, 0x73, 0x69, 
	0x74, 0x69, 0x6f, 0x6e, 0x3b, 0x0a, 0x20, 0x20, 0x67, 0x6c, 0x5f, 
	0x50, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x3d, 0x20, 
	0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x3b, 0x0a, 0x7d, 
	0x0a, 0x0a, 0x00, 0x00, 0x03, 0xe7, 0x04, 0xb0, 0xb0, 0xca, 0xea, 
	0x0c, 0x06, 0x8f, 0x96, 0x00, 0x01, 0x00, 0x00, 0xa8, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x53, 0x68, 0x64, 0x72, 0x07, 
	0x00, 0x01, 0x00, 0x01, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x64, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 
	0x00, 0xff, 0xff, 0xff, 0xff, 0x41, 0x00, 0x0c, 0x00, 0x0c, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 
	0x17, 0x00, 0x02, 0x10, 0x00, 0x04, 0x03, 0x00, 0xff, 0x03, 0xeb, 
	0xbe, 0x08, 0x00, 0x00, 0x00, 0x00, 0x21, 0x80, 0xbe, 0xf2, 0x02, 
	0x00, 0x7e, 0xcf, 0x08, 0x00, 0xf8, 0x04, 0x05, 0x06, 0x00, 0x0f, 
	0x02, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0xbf, 
	0x39, 0x6a, 0x06, 0x00, 0x04, 0x00, 0x00, 0x5b, 0x00, 0x01, 0x00, 
	0x00, 0x90, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x12, 0x00, 
	0x00, 0x00, 0x17, 0x00, 0x02, 0x10, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x4f, 0x72, 0x62, 0x53, 0x68, 0x64, 0x72, 0x07, 
	0x47, 0x24, 0x00, 0x00, 0x02, 0x02, 0x0c, 0x00, 0xb0, 0xb0, 0xca, 
	0xea, 0x0c, 0x06, 0x8f, 0x96, 0x2c, 0x09, 0xba, 0x68, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x2c, 0x00, 0x00, 0x00, 0x02, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x18, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x03, 0x2e, 
	0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x26, 
	0x00, 0x00, 0x00, 0x61, 0x5f, 0x70, 0x6f, 0x73, 0x69, 0x74, 0x69, 
	0x6f, 0x6e, 0x00, 0x41, 0x5f, 0x50, 0x4f, 0x53, 0x49, 0x54, 0x49, 
	0x4f, 0x4e, 0x00, 0x67, 0x6c, 0x5f, 0x50, 0x6f, 0x73, 0x69, 0x74, 
	0x69, 0x6f, 0x6e, 0x00, 0x28, 0x6e, 0x6f, 0x5f, 0x6e, 0x61, 0x6d, 
	0x65, 0x29, 0x00
};

const int vs_clear_glsl_ps4_length = 476;

extern const uint32_t vs_clear_pssl_size;
extern const uint8_t  *vs_clear_pssl;

