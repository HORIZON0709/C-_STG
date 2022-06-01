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
 134;
 -73.08324;72.03062;-45.77713;,
 73.08324;72.03062;-45.77713;,
 73.08324;66.76627;-45.77713;,
 -73.08324;66.76627;-45.77713;,
 73.08324;72.03062;-45.77713;,
 73.08324;72.03062;45.77713;,
 73.08324;66.76627;45.77713;,
 73.08324;66.76627;-45.77713;,
 73.08324;72.03062;45.77713;,
 -73.08324;72.03062;45.77713;,
 -73.08324;66.76627;45.77713;,
 73.08324;66.76627;45.77713;,
 -73.08324;72.03062;45.77713;,
 -73.08324;72.03062;-45.77713;,
 -73.08324;66.76627;-45.77713;,
 -73.08324;66.76627;45.77713;,
 73.08324;72.03062;-45.77713;,
 -73.08324;72.03062;-45.77713;,
 -73.08324;66.76627;-45.77713;,
 73.08324;66.76627;-45.77713;,
 -66.10294;70.26857;-40.95233;,
 66.10294;70.26857;-40.95233;,
 66.10294;60.36908;-40.95233;,
 -66.10294;60.36908;-40.95233;,
 57.47922;70.26857;-32.39018;,
 -57.47922;70.26857;-32.39018;,
 -57.47922;60.36908;-32.39018;,
 57.47922;60.36908;-32.39018;,
 66.10294;70.26857;40.95233;,
 66.10294;60.36908;40.95233;,
 57.47922;70.26857;32.39018;,
 57.47922;60.36908;32.39018;,
 -66.10294;70.26857;40.95233;,
 -66.10294;60.36908;40.95233;,
 -57.47922;70.26857;32.39018;,
 -57.47922;60.36908;32.39018;,
 -66.10294;70.26857;-40.95233;,
 -66.10294;60.36908;-40.95233;,
 -57.47922;70.26857;-32.39018;,
 -57.47922;60.36908;-32.39018;,
 57.47922;70.26857;-32.39018;,
 66.10294;70.26857;-40.95233;,
 -66.10294;60.36908;-40.95233;,
 66.10294;60.36908;-40.95233;,
 57.47922;60.36908;-32.39018;,
 -57.47922;60.36908;-32.39018;,
 57.47922;70.26857;32.39018;,
 66.10294;70.26857;40.95233;,
 66.10294;60.36908;40.95233;,
 57.47922;60.36908;32.39018;,
 -57.47922;70.26857;32.39018;,
 -66.10294;70.26857;40.95233;,
 -66.10294;60.36908;40.95233;,
 -57.47922;60.36908;32.39018;,
 -69.50061;67.72609;-42.82911;,
 -56.72872;67.72609;-42.82911;,
 -59.56952;0.02165;-39.98820;,
 -66.65976;0.02165;-39.98820;,
 -56.72872;67.72609;-42.82911;,
 -56.72872;67.72609;-30.05729;,
 -59.56952;0.02165;-32.89816;,
 -59.56952;0.02165;-39.98820;,
 -56.72872;67.72609;-30.05729;,
 -69.50061;67.72609;-30.05729;,
 -66.65976;0.02165;-32.89816;,
 -59.56952;0.02165;-32.89816;,
 -69.50061;67.72609;-30.05729;,
 -69.50061;67.72609;-42.82911;,
 -66.65976;0.02165;-39.98820;,
 -66.65976;0.02165;-32.89816;,
 -56.72872;67.72609;-42.82911;,
 -69.50061;67.72609;-42.82911;,
 -66.65976;0.02165;-39.98820;,
 -59.56952;0.02165;-39.98820;,
 -69.50061;67.72609;30.44213;,
 -56.72872;67.72609;30.44213;,
 -59.56952;0.02165;33.28300;,
 -66.65976;0.02165;33.28300;,
 -56.72872;67.72609;30.44213;,
 -56.72872;67.72609;43.21393;,
 -59.56952;0.02165;40.37305;,
 -59.56952;0.02165;33.28300;,
 -56.72872;67.72609;43.21393;,
 -69.50061;67.72609;43.21393;,
 -66.65976;0.02165;40.37305;,
 -59.56952;0.02165;40.37305;,
 -69.50061;67.72609;43.21393;,
 -69.50061;67.72609;30.44213;,
 -66.65976;0.02165;33.28300;,
 -66.65976;0.02165;40.37305;,
 -56.72872;67.72609;30.44213;,
 -69.50061;67.72609;30.44213;,
 -66.65976;0.02165;33.28300;,
 -59.56952;0.02165;33.28300;,
 56.72772;67.72609;30.44213;,
 69.49954;67.72609;30.44213;,
 66.65876;0.02165;33.28300;,
 59.56854;0.02165;33.28300;,
 69.49954;67.72609;30.44213;,
 69.49954;67.72609;43.21393;,
 66.65876;0.02165;40.37305;,
 66.65876;0.02165;33.28300;,
 69.49954;67.72609;43.21393;,
 56.72772;67.72609;43.21393;,
 59.56854;0.02165;40.37305;,
 66.65876;0.02165;40.37305;,
 56.72772;67.72609;43.21393;,
 56.72772;67.72609;30.44213;,
 59.56854;0.02165;33.28300;,
 59.56854;0.02165;40.37305;,
 69.49954;67.72609;30.44213;,
 56.72772;67.72609;30.44213;,
 59.56854;0.02165;33.28300;,
 66.65876;0.02165;33.28300;,
 56.72772;67.72609;-42.82911;,
 69.49954;67.72609;-42.82911;,
 66.65876;0.02165;-39.98820;,
 59.56854;0.02165;-39.98820;,
 69.49954;67.72609;-42.82911;,
 69.49954;67.72609;-30.05729;,
 66.65876;0.02165;-32.89816;,
 66.65876;0.02165;-39.98820;,
 69.49954;67.72609;-30.05729;,
 56.72772;67.72609;-30.05729;,
 59.56854;0.02165;-32.89816;,
 66.65876;0.02165;-32.89816;,
 56.72772;67.72609;-30.05729;,
 56.72772;67.72609;-42.82911;,
 59.56854;0.02165;-39.98820;,
 59.56854;0.02165;-32.89816;,
 69.49954;67.72609;-42.82911;,
 56.72772;67.72609;-42.82911;,
 59.56854;0.02165;-39.98820;,
 66.65876;0.02165;-39.98820;;
 
 46;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;21,28,29,22;,
 4;30,24,27,31;,
 4;28,32,33,29;,
 4;34,30,31,35;,
 4;32,36,37,33;,
 4;38,34,35,39;,
 4;20,25,40,41;,
 4;42,43,44,45;,
 4;41,40,46,47;,
 4;43,48,49,44;,
 4;47,46,50,51;,
 4;48,52,53,49;,
 4;51,50,25,20;,
 4;52,42,45,53;,
 4;54,55,56,57;,
 4;58,59,60,61;,
 4;62,63,64,65;,
 4;66,67,68,69;,
 4;66,59,70,71;,
 4;72,73,60,69;,
 4;74,75,76,77;,
 4;78,79,80,81;,
 4;82,83,84,85;,
 4;86,87,88,89;,
 4;86,79,90,91;,
 4;92,93,80,89;,
 4;94,95,96,97;,
 4;98,99,100,101;,
 4;102,103,104,105;,
 4;106,107,108,109;,
 4;106,99,110,111;,
 4;112,113,100,109;,
 4;114,115,116,117;,
 4;118,119,120,121;,
 4;122,123,124,125;,
 4;126,127,128,129;,
 4;126,119,130,131;,
 4;132,133,120,129;;
 
 MeshMaterialList {
  1;
  46;
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
   0.360800;0.244800;0.150400;1.000000;;
   5.000000;
   0.400000;0.400000;0.400000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  25;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.041924;-0.999121;,
  0.999121;-0.041922;-0.000000;,
  0.000000;-0.041923;0.999121;,
  0.000000;-0.041923;-0.999121;,
  0.999121;-0.041922;-0.000000;,
  0.000000;-0.041923;0.999121;,
  0.999121;-0.041922;-0.000000;,
  0.000000;-0.041924;-0.999121;,
  -0.999121;-0.041923;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.999121;-0.041922;0.000000;,
  -0.999121;-0.041922;0.000000;;
  46;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;8,8,8,8;,
  4;7,7,7,7;,
  4;9,9,9,9;,
  4;8,8,8,8;,
  4;6,6,6,6;,
  4;9,9,9,9;,
  4;7,7,7,7;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;15,15,15,15;,
  4;18,18,18,18;,
  4;17,17,17,17;,
  4;23,23,23,23;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;19,19,19,19;,
  4;18,18,18,18;,
  4;14,14,14,14;,
  4;24,24,24,24;,
  4;21,21,21,21;,
  4;22,22,22,22;;
 }
 MeshTextureCoords {
  134;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
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
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
