xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 168;
 -0.00853;-0.00010;0.00012;,
 -0.00853;-0.18468;-0.18445;,
 -0.00853;-0.00010;-0.26090;,
 -0.00851;-0.26110;0.00012;,
 -0.00853;-0.18468;0.18469;,
 -0.00853;-0.00010;0.26114;,
 -0.00853;0.18447;0.18469;,
 -0.00851;0.26090;0.00012;,
 -0.00853;0.18447;-0.18445;,
 -0.12965;-0.60014;-0.59993;,
 -0.12965;-0.00009;-0.84848;,
 -0.12965;-0.84870;0.00012;,
 -0.12965;-0.60014;0.60017;,
 -0.12965;-0.00009;0.84872;,
 -0.12965;0.59996;0.60017;,
 -0.12964;0.84850;0.00012;,
 -0.12965;0.59996;-0.59993;,
 -0.47434;-0.95240;-0.95216;,
 -0.47433;-0.00009;-1.34661;,
 -0.47433;-1.34683;0.00012;,
 -0.47434;-0.95240;0.95240;,
 -0.47433;-0.00009;1.34685;,
 -0.47434;0.95217;0.95240;,
 -0.47434;1.34663;0.00012;,
 -0.47434;0.95217;-0.95216;,
 -0.99011;-1.18773;-1.18751;,
 -0.99011;-0.00010;-1.67945;,
 -0.99010;-1.67966;0.00012;,
 -0.99011;-1.18773;1.18775;,
 -0.99011;-0.00010;1.67969;,
 -0.99011;1.18754;1.18775;,
 -0.99011;1.67948;0.00012;,
 -0.99011;1.18754;-1.18751;,
 -1.59856;-1.27036;-1.27016;,
 -1.59857;-0.00009;-1.79632;,
 -1.59857;-1.79656;0.00012;,
 -1.59856;-1.27036;1.27040;,
 -1.59857;-0.00009;1.79656;,
 -1.59857;1.27018;1.27040;,
 -1.59857;1.79634;0.00012;,
 -1.59857;1.27018;-1.27016;,
 -10.56396;-0.00010;-1.79632;,
 -10.56395;-1.27037;-1.27016;,
 -11.17245;-1.18773;-1.18751;,
 -11.17245;-0.00009;-1.67945;,
 -10.56396;-1.79656;0.00012;,
 -11.17245;-1.67967;0.00012;,
 -10.56395;-1.27037;1.27040;,
 -11.17245;-1.18773;1.18775;,
 -10.56396;-0.00010;1.79656;,
 -11.17245;-0.00009;1.67969;,
 -10.56396;1.27018;1.27040;,
 -11.17245;1.18754;1.18775;,
 -10.56396;1.79634;0.00012;,
 -11.17244;1.67947;0.00012;,
 -10.56396;1.27018;-1.27016;,
 -11.17245;1.18754;-1.18751;,
 -11.68824;-0.95239;-0.95216;,
 -11.68824;-0.00009;-1.34661;,
 -11.68825;-1.34683;0.00012;,
 -11.68824;-0.95239;0.95240;,
 -11.68824;-0.00009;1.34685;,
 -11.68823;0.95218;0.95240;,
 -11.68824;1.34664;0.00012;,
 -11.68823;0.95218;-0.95216;,
 -12.03288;-0.60014;-0.59993;,
 -12.03288;-0.00009;-0.84848;,
 -12.03288;-0.84872;0.00012;,
 -12.03288;-0.60014;0.60017;,
 -12.03288;-0.00009;0.84872;,
 -12.03288;0.59995;0.60017;,
 -12.03288;0.84849;0.00012;,
 -12.03288;0.59995;-0.59993;,
 -12.15392;-0.18468;-0.18445;,
 -12.15393;-0.00009;-0.26090;,
 -12.15392;-0.26110;0.00012;,
 -12.15392;-0.18468;0.18469;,
 -12.15393;-0.00009;0.26114;,
 -12.15392;0.18447;0.18469;,
 -12.15392;0.26091;0.00012;,
 -12.15392;0.18447;-0.18445;,
 -12.15393;-0.00009;0.00012;,
 -6.65373;-1.27037;-1.27016;,
 -6.66038;-0.00010;-1.79632;,
 -6.65098;-1.79656;0.00012;,
 -6.65373;-1.27037;1.27040;,
 -6.66038;-0.00010;1.79656;,
 -6.66703;1.27018;1.27040;,
 -6.66979;1.79634;0.00012;,
 -6.66703;1.27018;-1.27016;,
 -9.76808;0.02741;0.09829;,
 -10.04022;-0.73893;-0.81502;,
 -10.04022;0.02741;-1.09395;,
 -9.76808;0.02741;0.09829;,
 -10.04021;-1.14671;-0.10874;,
 -9.76808;0.02741;0.09829;,
 -10.04022;-1.00509;0.69441;,
 -9.76808;0.02741;0.09829;,
 -10.04022;-0.38036;1.21863;,
 -9.76808;0.02741;0.09829;,
 -10.04022;0.43519;1.21863;,
 -9.76808;0.02741;0.09829;,
 -10.04021;1.05993;0.69441;,
 -9.76808;0.02741;0.09829;,
 -10.04022;1.20154;-0.10874;,
 -9.76808;0.02741;0.09829;,
 -10.04020;0.79376;-0.81502;,
 -9.76808;0.02741;0.09829;,
 -10.04022;0.02741;-1.09395;,
 -10.80268;-1.35352;-1.54744;,
 -10.80268;0.02741;-2.05005;,
 -10.80268;-2.08828;-0.27476;,
 -10.80269;-1.83309;1.17246;,
 -10.80268;-0.70736;2.11707;,
 -10.80269;0.76219;2.11707;,
 -10.80269;1.88795;1.17246;,
 -10.80269;2.14313;-0.27476;,
 -10.80268;1.40835;-1.54744;,
 -10.80268;0.02741;-2.05005;,
 -11.90447;-1.69458;-1.95389;,
 -11.90447;0.02741;-2.58064;,
 -11.90448;-2.61082;-0.36690;,
 -11.90447;-2.29261;1.43776;,
 -11.90447;-0.88885;2.61567;,
 -11.90447;0.94366;2.61567;,
 -11.90448;2.34744;1.43776;,
 -11.90447;2.66566;-0.36690;,
 -11.90447;1.74940;-1.95389;,
 -11.90447;0.02741;-2.58064;,
 -13.12738;-1.69458;-1.95389;,
 -13.12738;0.02742;-2.58064;,
 -13.12738;-2.61083;-0.36690;,
 -13.12737;-2.29261;1.43776;,
 -13.12737;-0.88885;2.61567;,
 -13.12738;0.94366;2.61567;,
 -13.12739;2.34744;1.43776;,
 -13.12738;2.66565;-0.36690;,
 -13.12739;1.74942;-1.95389;,
 -13.12738;0.02742;-2.58064;,
 -14.22917;-1.35352;-1.54744;,
 -14.22918;0.02742;-2.05005;,
 -14.22917;-2.08829;-0.27476;,
 -14.22917;-1.83311;1.17246;,
 -14.22918;-0.70736;2.11707;,
 -14.22917;0.76218;2.11707;,
 -14.22916;1.88792;1.17246;,
 -14.22917;2.14311;-0.27476;,
 -14.22917;1.40834;-1.54744;,
 -14.22918;0.02742;-2.05005;,
 -14.99165;-0.73894;-0.81502;,
 -14.99164;0.02742;-1.09395;,
 -14.99164;-1.14671;-0.10874;,
 -14.99164;-1.00509;0.69441;,
 -14.99164;-0.38036;1.21863;,
 -14.99165;0.43518;1.21863;,
 -14.99164;1.05991;0.69441;,
 -14.99164;1.20154;-0.10874;,
 -14.99164;0.79376;-0.81502;,
 -14.99164;0.02742;-1.09395;,
 -15.26377;0.02742;0.09829;,
 -15.26377;0.02742;0.09829;,
 -15.26377;0.02742;0.09829;,
 -15.26377;0.02742;0.09829;,
 -15.26377;0.02742;0.09829;,
 -15.26377;0.02742;0.09829;,
 -15.26377;0.02742;0.09829;,
 -15.26377;0.02742;0.09829;,
 -15.26377;0.02742;0.09829;;
 
 159;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,2,8;,
 4;2,1,9,10;,
 4;1,3,11,9;,
 4;3,4,12,11;,
 4;4,5,13,12;,
 4;5,6,14,13;,
 4;6,7,15,14;,
 4;7,8,16,15;,
 4;8,2,10,16;,
 4;10,9,17,18;,
 4;9,11,19,17;,
 4;11,12,20,19;,
 4;12,13,21,20;,
 4;13,14,22,21;,
 4;14,15,23,22;,
 4;15,16,24,23;,
 4;16,10,18,24;,
 4;18,17,25,26;,
 4;17,19,27,25;,
 4;19,20,28,27;,
 4;20,21,29,28;,
 4;21,22,30,29;,
 4;22,23,31,30;,
 4;23,24,32,31;,
 4;24,18,26,32;,
 4;26,25,33,34;,
 4;25,27,35,33;,
 4;27,28,36,35;,
 4;28,29,37,36;,
 4;29,30,38,37;,
 4;30,31,39,38;,
 4;31,32,40,39;,
 4;32,26,34,40;,
 4;41,42,43,44;,
 4;42,45,46,43;,
 4;45,47,48,46;,
 4;47,49,50,48;,
 4;49,51,52,50;,
 4;51,53,54,52;,
 4;53,55,56,54;,
 4;55,41,44,56;,
 4;44,43,57,58;,
 4;43,46,59,57;,
 4;46,48,60,59;,
 4;48,50,61,60;,
 4;50,52,62,61;,
 4;52,54,63,62;,
 4;54,56,64,63;,
 4;56,44,58,64;,
 4;58,57,65,66;,
 4;57,59,67,65;,
 4;59,60,68,67;,
 4;60,61,69,68;,
 4;61,62,70,69;,
 4;62,63,71,70;,
 4;63,64,72,71;,
 4;64,58,66,72;,
 4;66,65,73,74;,
 4;65,67,75,73;,
 4;67,68,76,75;,
 4;68,69,77,76;,
 4;69,70,78,77;,
 4;70,71,79,78;,
 4;71,72,80,79;,
 4;72,66,74,80;,
 3;74,73,81;,
 3;73,75,81;,
 3;75,76,81;,
 3;76,77,81;,
 3;77,78,81;,
 3;78,79,81;,
 3;79,80,81;,
 3;80,74,81;,
 4;82,42,41,83;,
 4;82,83,34,33;,
 4;84,45,42,82;,
 4;84,82,33,35;,
 4;85,47,45,84;,
 4;85,84,35,36;,
 4;86,49,47,85;,
 4;86,85,36,37;,
 4;87,51,49,86;,
 4;87,86,37,38;,
 4;88,53,51,87;,
 4;88,87,38,39;,
 4;89,55,53,88;,
 4;89,88,39,40;,
 4;83,41,55,89;,
 4;83,89,40,34;,
 3;90,91,92;,
 3;93,94,91;,
 3;95,96,94;,
 3;97,98,96;,
 3;99,100,98;,
 3;101,102,100;,
 3;103,104,102;,
 3;105,106,104;,
 3;107,108,106;,
 4;92,91,109,110;,
 4;91,94,111,109;,
 4;94,96,112,111;,
 4;96,98,113,112;,
 4;98,100,114,113;,
 4;100,102,115,114;,
 4;102,104,116,115;,
 4;104,106,117,116;,
 4;106,108,118,117;,
 4;110,109,119,120;,
 4;109,111,121,119;,
 4;111,112,122,121;,
 4;112,113,123,122;,
 4;113,114,124,123;,
 4;114,115,125,124;,
 4;115,116,126,125;,
 4;116,117,127,126;,
 4;117,118,128,127;,
 4;120,119,129,130;,
 4;119,121,131,129;,
 4;121,122,132,131;,
 4;122,123,133,132;,
 4;123,124,134,133;,
 4;124,125,135,134;,
 4;125,126,136,135;,
 4;126,127,137,136;,
 4;127,128,138,137;,
 4;130,129,139,140;,
 4;129,131,141,139;,
 4;131,132,142,141;,
 4;132,133,143,142;,
 4;133,134,144,143;,
 4;134,135,145,144;,
 4;135,136,146,145;,
 4;136,137,147,146;,
 4;137,138,148,147;,
 4;140,139,149,150;,
 4;139,141,151,149;,
 4;141,142,152,151;,
 4;142,143,153,152;,
 4;143,144,154,153;,
 4;144,145,155,154;,
 4;145,146,156,155;,
 4;146,147,157,156;,
 4;147,148,158,157;,
 3;150,149,159;,
 3;149,151,160;,
 3;151,152,161;,
 3;152,153,162;,
 3;153,154,163;,
 3;154,155,164;,
 3;155,156,165;,
 3;156,157,166;,
 3;157,158,167;;
 
 MeshMaterialList {
  6;
  159;
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  0,
  4,
  0,
  4,
  0,
  4,
  0,
  4,
  0,
  4,
  0,
  4,
  0,
  4,
  0,
  4,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.680800;0.520800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.031200;0.360800;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.599200;0.599200;0.599200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.500000;0.500000;0.500000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.600000;0.902000;1.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  146;
  1.000000;0.000004;0.000000;,
  0.994857;0.000006;-0.101292;,
  0.994856;-0.071612;-0.071642;,
  0.994859;-0.101268;-0.000000;,
  0.994856;-0.071611;0.071642;,
  0.994857;0.000006;0.101292;,
  0.994856;0.071613;0.071645;,
  0.994860;0.101259;-0.000000;,
  0.994856;0.071613;-0.071645;,
  0.920320;0.000004;-0.391167;,
  0.920319;-0.276593;-0.276602;,
  0.920322;-0.391162;-0.000000;,
  0.920320;-0.276592;0.276602;,
  0.920319;0.000004;0.391168;,
  0.920317;0.276600;0.276605;,
  0.920319;0.391168;0.000000;,
  0.920317;0.276600;-0.276604;,
  0.697768;0.000003;-0.716324;,
  0.697766;-0.506519;-0.506518;,
  0.697765;-0.716327;-0.000000;,
  0.697767;-0.506518;0.506518;,
  0.697767;0.000003;0.716324;,
  0.697765;0.506521;0.506518;,
  0.697766;0.716326;0.000000;,
  0.697765;0.506521;-0.506517;,
  0.373988;0.000001;-0.927433;,
  0.373985;-0.655795;-0.655795;,
  0.373987;-0.927434;0.000000;,
  0.373986;-0.655795;0.655796;,
  0.373988;0.000001;0.927434;,
  0.373990;0.655795;0.655793;,
  0.373992;0.927432;0.000000;,
  0.373991;0.655795;-0.655793;,
  0.094867;-0.000001;-0.995490;,
  0.094870;-0.703912;-0.703923;,
  0.094876;-0.995489;0.000000;,
  0.094870;-0.703912;0.703923;,
  0.094867;-0.000001;0.995490;,
  0.094865;0.703919;0.703917;,
  0.094862;0.995490;0.000000;,
  0.094866;0.703919;-0.703917;,
  -0.094863;-0.000001;-0.995490;,
  -0.094864;-0.703913;-0.703923;,
  -0.094866;-0.995490;0.000000;,
  -0.094864;-0.703913;0.703923;,
  -0.094862;-0.000001;0.995490;,
  -0.094862;0.703919;0.703917;,
  -0.094861;0.995490;0.000000;,
  -0.094862;0.703919;-0.703917;,
  -0.373977;0.000002;-0.927438;,
  -0.373975;-0.655797;-0.655799;,
  -0.373976;-0.927438;0.000000;,
  -0.373975;-0.655797;0.655800;,
  -0.373977;0.000001;0.927438;,
  -0.373976;0.655800;0.655796;,
  -0.373975;0.927439;0.000000;,
  -0.373977;0.655799;-0.655796;,
  -0.697785;0.000005;-0.716307;,
  -0.697782;-0.506506;-0.506509;,
  -0.697781;-0.716311;0.000000;,
  -0.697782;-0.506506;0.506510;,
  -0.697784;0.000005;0.716308;,
  -0.697783;0.506507;0.506506;,
  -0.697787;0.716305;0.000000;,
  -0.697785;0.506507;-0.506505;,
  -0.920358;0.000005;-0.391077;,
  -0.920356;-0.276538;-0.276535;,
  -0.920357;-0.391078;0.000000;,
  -0.920357;-0.276536;0.276533;,
  -0.920359;0.000007;0.391075;,
  -0.920356;0.276540;0.276532;,
  -0.920359;0.391075;-0.000001;,
  -0.920356;0.276542;-0.276532;,
  -0.994864;0.000002;-0.101225;,
  -0.994862;-0.071600;-0.071579;,
  -0.994862;-0.101242;-0.000000;,
  -0.994862;-0.071599;0.071576;,
  -0.994864;0.000003;0.101222;,
  -0.994862;0.071601;0.071578;,
  -0.994862;0.101241;-0.000001;,
  -0.994862;0.071603;-0.071579;,
  -1.000000;0.000000;0.000000;,
  0.000000;-0.000001;-1.000000;,
  0.000000;-0.707100;-0.707113;,
  0.000000;-1.000000;0.000000;,
  0.000000;-0.707100;0.707114;,
  0.000000;-0.000001;1.000000;,
  -0.000000;0.707107;0.707107;,
  -0.000000;1.000000;0.000000;,
  -0.000000;0.707107;-0.707106;,
  1.000000;-0.000002;0.000001;,
  0.902045;-0.000006;-0.431642;,
  0.902045;-0.277451;-0.330659;,
  0.902046;-0.425082;-0.074951;,
  0.902043;-0.373814;0.215826;,
  0.902045;-0.147632;0.405610;,
  0.902044;0.147628;0.405613;,
  0.902047;0.373810;0.215819;,
  0.902045;0.425085;-0.074952;,
  0.902048;0.277451;-0.330653;,
  0.625802;-0.000002;-0.779982;,
  0.625804;-0.501362;-0.597499;,
  0.625804;-0.768132;-0.135438;,
  0.625803;-0.675484;0.389991;,
  0.625805;-0.266770;0.732940;,
  0.625801;0.266768;0.732944;,
  0.625802;0.675484;0.389992;,
  0.625802;0.768133;-0.135442;,
  0.625803;0.501362;-0.597501;,
  0.223760;-0.000001;-0.974644;,
  0.223760;-0.626491;-0.746620;,
  0.223762;-0.959837;-0.169242;,
  0.223763;-0.844067;0.487320;,
  0.223763;-0.333350;0.915865;,
  0.223761;0.333346;0.915866;,
  0.223758;0.844066;0.487325;,
  0.223758;0.959838;-0.169244;,
  0.223760;0.626489;-0.746621;,
  -0.223758;-0.000000;-0.974645;,
  -0.223759;-0.626490;-0.746621;,
  -0.223757;-0.959838;-0.169243;,
  -0.223758;-0.844068;0.487321;,
  -0.223760;-0.333350;0.915865;,
  -0.223761;0.333347;0.915866;,
  -0.223764;0.844065;0.487323;,
  -0.223764;0.959837;-0.169243;,
  -0.223761;0.626490;-0.746620;,
  -0.625802;0.000003;-0.779982;,
  -0.625802;-0.501364;-0.597500;,
  -0.625801;-0.768134;-0.135440;,
  -0.625802;-0.675485;0.389991;,
  -0.625802;-0.266771;0.732943;,
  -0.625802;0.266771;0.732943;,
  -0.625802;0.675484;0.389992;,
  -0.625805;0.768130;-0.135439;,
  -0.625804;0.501363;-0.597499;,
  -0.902047;0.000008;-0.431638;,
  -0.902048;-0.277450;-0.330651;,
  -0.902046;-0.425082;-0.074948;,
  -0.902047;-0.373809;0.215820;,
  -0.902045;-0.147633;0.405609;,
  -0.902047;0.147631;0.405606;,
  -0.902043;0.373817;0.215821;,
  -0.902047;0.425081;-0.074952;,
  -0.902045;0.277454;-0.330657;,
  -1.000000;0.000002;0.000001;;
  159;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,25,33,40;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,41,49,56;,
  4;49,50,58,57;,
  4;50,51,59,58;,
  4;51,52,60,59;,
  4;52,53,61,60;,
  4;53,54,62,61;,
  4;54,55,63,62;,
  4;55,56,64,63;,
  4;56,49,57,64;,
  4;57,58,66,65;,
  4;58,59,67,66;,
  4;59,60,68,67;,
  4;60,61,69,68;,
  4;61,62,70,69;,
  4;62,63,71,70;,
  4;63,64,72,71;,
  4;64,57,65,72;,
  4;65,66,74,73;,
  4;66,67,75,74;,
  4;67,68,76,75;,
  4;68,69,77,76;,
  4;69,70,78,77;,
  4;70,71,79,78;,
  4;71,72,80,79;,
  4;72,65,73,80;,
  3;73,74,81;,
  3;74,75,81;,
  3;75,76,81;,
  3;76,77,81;,
  3;77,78,81;,
  3;78,79,81;,
  3;79,80,81;,
  3;80,73,81;,
  4;83,42,41,82;,
  4;83,82,33,34;,
  4;84,43,42,83;,
  4;84,83,34,35;,
  4;85,44,43,84;,
  4;85,84,35,36;,
  4;86,45,44,85;,
  4;86,85,36,37;,
  4;87,46,45,86;,
  4;87,86,37,38;,
  4;88,47,46,87;,
  4;88,87,38,39;,
  4;89,48,47,88;,
  4;89,88,39,40;,
  4;82,41,48,89;,
  4;82,89,40,33;,
  3;90,92,91;,
  3;90,93,92;,
  3;90,94,93;,
  3;90,95,94;,
  3;90,96,95;,
  3;90,97,96;,
  3;90,98,97;,
  3;90,99,98;,
  3;90,91,99;,
  4;91,92,101,100;,
  4;92,93,102,101;,
  4;93,94,103,102;,
  4;94,95,104,103;,
  4;95,96,105,104;,
  4;96,97,106,105;,
  4;97,98,107,106;,
  4;98,99,108,107;,
  4;99,91,100,108;,
  4;100,101,110,109;,
  4;101,102,111,110;,
  4;102,103,112,111;,
  4;103,104,113,112;,
  4;104,105,114,113;,
  4;105,106,115,114;,
  4;106,107,116,115;,
  4;107,108,117,116;,
  4;108,100,109,117;,
  4;109,110,119,118;,
  4;110,111,120,119;,
  4;111,112,121,120;,
  4;112,113,122,121;,
  4;113,114,123,122;,
  4;114,115,124,123;,
  4;115,116,125,124;,
  4;116,117,126,125;,
  4;117,109,118,126;,
  4;118,119,128,127;,
  4;119,120,129,128;,
  4;120,121,130,129;,
  4;121,122,131,130;,
  4;122,123,132,131;,
  4;123,124,133,132;,
  4;124,125,134,133;,
  4;125,126,135,134;,
  4;126,118,127,135;,
  4;127,128,137,136;,
  4;128,129,138,137;,
  4;129,130,139,138;,
  4;130,131,140,139;,
  4;131,132,141,140;,
  4;132,133,142,141;,
  4;133,134,143,142;,
  4;134,135,144,143;,
  4;135,127,136,144;,
  3;136,137,145;,
  3;137,138,145;,
  3;138,139,145;,
  3;139,140,145;,
  3;140,141,145;,
  3;141,142,145;,
  3;142,143,145;,
  3;143,144,145;,
  3;144,136,145;;
 }
 MeshTextureCoords {
  168;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.055560;0.000000;,
  0.111110;0.142860;,
  0.000000;0.142860;,
  0.166670;0.000000;,
  0.222220;0.142860;,
  0.277780;0.000000;,
  0.333330;0.142860;,
  0.388890;0.000000;,
  0.444440;0.142860;,
  0.500000;0.000000;,
  0.555560;0.142860;,
  0.611110;0.000000;,
  0.666670;0.142860;,
  0.722220;0.000000;,
  0.777780;0.142860;,
  0.833330;0.000000;,
  0.888890;0.142860;,
  0.944440;0.000000;,
  1.000000;0.142860;,
  0.111110;0.285710;,
  0.000000;0.285710;,
  0.222220;0.285710;,
  0.333330;0.285710;,
  0.444440;0.285710;,
  0.555560;0.285710;,
  0.666670;0.285710;,
  0.777780;0.285710;,
  0.888890;0.285710;,
  1.000000;0.285710;,
  0.111110;0.428570;,
  0.000000;0.428570;,
  0.222220;0.428570;,
  0.333330;0.428570;,
  0.444440;0.428570;,
  0.555560;0.428570;,
  0.666670;0.428570;,
  0.777780;0.428570;,
  0.888890;0.428570;,
  1.000000;0.428570;,
  0.111110;0.571430;,
  0.000000;0.571430;,
  0.222220;0.571430;,
  0.333330;0.571430;,
  0.444440;0.571430;,
  0.555560;0.571430;,
  0.666670;0.571430;,
  0.777780;0.571430;,
  0.888890;0.571430;,
  1.000000;0.571430;,
  0.111110;0.714290;,
  0.000000;0.714290;,
  0.222220;0.714290;,
  0.333330;0.714290;,
  0.444440;0.714290;,
  0.555560;0.714290;,
  0.666670;0.714290;,
  0.777780;0.714290;,
  0.888890;0.714290;,
  1.000000;0.714290;,
  0.111110;0.857140;,
  0.000000;0.857140;,
  0.222220;0.857140;,
  0.333330;0.857140;,
  0.444440;0.857140;,
  0.555560;0.857140;,
  0.666670;0.857140;,
  0.777780;0.857140;,
  0.888890;0.857140;,
  1.000000;0.857140;,
  0.055560;1.000000;,
  0.166670;1.000000;,
  0.277780;1.000000;,
  0.388890;1.000000;,
  0.500000;1.000000;,
  0.611110;1.000000;,
  0.722220;1.000000;,
  0.833330;1.000000;,
  0.944440;1.000000;;
 }
}
