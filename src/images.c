#include "config.h"
#include <lcdfgif/gif.h>


static const unsigned char buttons_gif_data[] = {
71,73,70,56,57,97,38,0,56,0,244,0,0,0,0,0,204,204,204,255,
255,255,119,136,153,47,79,79,112,128,144,0,0,0,255,50,46,138,16,0,
255,126,111,154,154,154,211,211,211,255,165,0,175,113,0,248,211,19,191,118,
122,34,38,38,255,255,0,255,248,220,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,33,206,4,104,105,110,116,0,33,249,4,
1,0,0,0,0,44,0,0,0,0,38,0,56,0,0,5,254,32,32,142,
100,105,158,104,170,174,108,107,188,240,219,206,192,27,220,248,45,211,168,157,
255,58,3,207,100,192,9,128,57,225,112,84,12,8,158,200,228,178,102,124,
30,163,186,101,211,122,197,6,148,180,166,19,234,197,129,93,55,110,217,28,
174,118,215,223,153,216,9,151,162,235,200,179,106,142,103,223,251,118,44,124,
128,122,41,131,95,136,69,62,63,133,61,121,64,135,141,39,145,144,121,109,
64,3,3,55,153,150,151,152,153,154,157,158,57,160,161,140,83,131,160,162,
67,139,56,170,73,146,114,164,156,129,83,34,124,175,89,182,36,98,185,113,
187,37,189,180,177,168,155,180,191,192,76,48,165,49,201,188,4,4,49,5,
5,196,172,6,208,4,5,217,217,59,206,53,209,49,6,212,222,183,215,216,
218,218,221,206,215,225,226,213,60,47,216,208,232,234,235,230,208,245,228,237,
228,147,48,222,249,252,202,213,8,72,68,136,30,128,193,222,213,48,152,80,
208,59,25,10,39,185,48,8,166,27,68,139,205,246,92,28,8,113,33,69,
101,43,50,98,4,185,144,100,72,37,59,29,212,165,68,169,112,165,73,151,
2,29,10,252,248,177,36,205,147,47,89,230,36,200,179,167,207,159,36,66,
0,0,33,206,3,110,101,119,0,33,249,4,1,0,0,0,0,44,0,0,
0,0,38,0,56,0,0,5,254,32,32,142,100,105,158,104,170,154,70,219,
174,112,233,186,71,253,198,164,59,206,117,239,223,49,23,98,102,64,248,142,
61,96,138,134,236,33,158,80,232,79,213,66,70,159,86,35,246,160,204,25,
157,219,166,239,187,53,156,138,223,131,116,28,29,59,109,102,89,186,13,198,
174,183,233,184,72,88,63,134,181,100,53,101,122,104,115,97,106,134,111,137,
92,57,126,105,136,134,129,145,54,59,143,107,144,118,116,150,88,64,69,117,
120,87,151,155,95,132,160,161,167,115,108,164,149,100,168,161,110,125,140,123,
174,109,175,111,130,101,172,168,136,159,169,184,70,9,165,135,170,170,128,125,
193,94,143,142,142,151,188,7,200,172,98,184,203,212,208,179,202,212,217,188,
9,214,45,195,89,77,135,192,157,205,98,229,142,220,122,0,133,210,177,204,
79,193,234,236,237,152,145,82,214,215,244,189,182,207,234,235,223,210,92,245,
72,39,3,141,190,98,135,8,202,193,118,16,91,60,22,6,15,182,83,200,
226,156,196,129,93,146,49,188,136,15,34,64,137,20,81,120,251,72,47,164,
200,121,28,96,31,194,24,73,242,8,183,142,84,70,234,123,169,18,199,58,
62,98,104,102,180,201,163,6,205,120,254,108,66,36,162,67,168,209,163,72,
147,42,77,250,162,232,77,121,80,131,60,189,73,181,147,153,166,65,151,196,
193,74,181,43,87,28,55,184,18,186,186,53,235,153,178,123,172,146,237,26,
4,109,81,177,107,193,142,77,11,53,238,210,187,120,243,234,221,11,35,4,
0,33,206,4,113,117,105,116,0,33,249,4,1,0,0,0,0,44,0,0,
0,0,38,0,56,0,0,5,254,32,32,142,100,105,158,104,170,174,108,235,
190,112,44,207,116,109,223,128,161,239,60,158,239,130,160,80,216,155,233,130,
138,161,146,168,139,25,150,80,168,225,117,20,38,163,203,38,235,185,188,98,
135,218,84,21,234,37,131,85,220,104,89,185,14,155,210,234,53,118,122,130,
127,239,231,183,25,31,165,151,236,2,114,124,68,122,67,130,124,11,11,65,
126,35,112,135,119,137,138,139,133,131,66,137,76,85,110,57,72,120,145,11,
112,60,92,140,155,149,2,60,152,71,154,57,143,74,161,162,167,170,6,94,
99,89,161,152,147,111,179,128,168,180,153,117,186,180,188,187,166,40,160,193,
188,139,166,132,117,146,139,195,166,99,169,203,111,158,137,207,173,118,163,141,
6,213,220,205,115,105,73,218,219,222,159,222,68,120,226,43,58,214,182,199,
108,196,91,59,36,167,86,129,156,10,227,78,225,247,73,249,250,50,142,40,
24,56,16,154,15,114,161,14,42,92,200,176,161,67,121,244,0,214,112,163,
170,161,196,136,97,50,210,209,56,15,205,198,41,32,63,230,248,177,173,133,
22,141,34,42,80,166,188,72,114,101,73,149,45,215,137,116,25,19,166,71,
154,45,155,132,28,169,83,94,199,149,59,113,86,20,195,242,70,207,135,36,
139,218,24,58,35,4,0,33,206,4,114,111,99,107,0,33,249,4,1,0,
0,0,0,44,0,0,0,0,20,0,20,0,0,5,95,32,32,142,100,105,
154,70,154,158,168,193,188,239,202,2,46,108,55,6,91,51,78,223,191,56,
20,204,71,236,5,73,53,7,143,184,60,138,146,202,101,212,231,132,14,129,
212,220,243,245,179,49,26,217,145,181,1,252,134,183,75,51,216,108,212,162,
149,224,95,220,249,46,18,233,79,178,189,173,107,196,169,120,37,41,126,132,
50,51,79,42,110,135,139,140,140,33,0,33,206,4,117,110,100,111,0,33,
249,4,1,0,0,0,0,44,0,0,0,0,38,0,56,0,0,5,254,32,
32,142,100,105,158,104,170,174,108,235,190,112,44,207,180,104,220,248,93,159,
120,226,255,184,221,232,246,43,2,117,53,131,113,233,67,32,99,68,230,18,
225,148,41,165,76,106,245,117,197,102,183,173,174,55,251,84,137,199,83,112,
234,140,54,82,13,43,229,227,33,157,219,191,240,117,194,206,239,247,211,121,
60,123,126,132,124,128,40,114,133,138,116,69,90,129,36,137,139,133,141,142,
38,145,146,126,148,149,144,131,152,132,63,90,111,37,151,158,134,77,161,106,
164,165,115,160,168,143,68,171,127,167,161,101,87,177,119,179,180,156,63,177,
154,186,187,188,158,190,155,192,193,146,173,174,130,75,139,195,162,202,123,203,
184,205,106,163,62,166,99,168,206,136,214,215,82,217,101,60,182,178,105,180,
143,122,198,140,110,174,230,107,6,84,193,228,196,46,55,239,95,229,51,244,
90,205,224,48,56,217,247,66,0,248,91,23,112,84,142,32,5,119,240,75,
8,137,29,195,33,14,31,10,140,104,16,162,13,56,8,47,78,132,232,16,
99,30,29,30,61,106,68,8,18,163,165,143,129,42,144,168,68,185,81,228,
201,141,22,91,162,116,153,49,230,147,149,26,97,222,100,135,147,102,200,145,
50,17,149,204,169,115,232,69,138,18,147,42,93,154,48,4,0,33,206,5,
99,108,101,97,110,0,33,249,4,1,0,0,2,0,44,0,0,0,0,38,
0,56,0,0,5,254,160,32,142,100,105,158,104,170,174,108,235,190,112,44,
207,36,0,208,47,64,16,55,206,234,187,158,15,5,128,236,130,67,34,196,
136,76,158,138,71,158,243,201,108,78,71,197,42,79,120,205,110,131,182,176,
24,87,20,71,207,96,90,25,138,70,219,100,186,101,123,46,205,209,131,144,
178,188,238,2,182,253,71,75,76,92,42,128,81,134,135,130,124,133,110,119,
59,130,70,132,79,135,142,137,131,133,90,149,90,144,139,37,108,136,109,123,
120,130,146,2,54,153,154,153,89,165,122,160,143,153,162,163,146,122,142,177,
4,182,164,158,75,174,81,184,170,187,53,187,103,182,183,168,104,192,193,121,
195,168,196,103,111,186,194,189,204,116,207,84,209,129,198,110,165,201,215,175,
142,219,38,89,221,183,212,224,79,226,188,71,213,49,171,223,67,237,127,230,
57,101,206,242,112,123,235,87,166,145,250,231,253,34,249,254,221,8,40,208,
94,18,130,239,158,85,11,83,99,32,192,129,8,223,72,236,49,241,161,41,
135,12,9,174,83,8,209,226,66,138,179,184,48,188,104,202,98,73,44,32,
31,195,137,20,50,146,228,71,147,158,40,186,36,89,178,98,199,153,49,89,
234,212,73,243,229,191,159,64,131,234,11,1,0,33,206,9,99,108,101,97,
110,45,108,105,116,0,33,249,4,1,0,0,2,0,44,0,0,0,0,38,
0,56,0,0,5,254,160,32,142,100,105,158,104,170,174,108,235,190,112,44,
207,100,20,209,111,68,16,55,206,234,187,158,15,21,129,236,130,67,34,196,
136,76,158,138,71,158,243,201,108,78,71,197,42,79,120,205,18,0,128,160,
109,76,198,21,193,224,168,90,76,59,3,180,235,163,77,166,91,198,239,210,
28,126,247,238,219,243,46,64,113,97,106,75,76,92,42,130,106,132,131,134,
128,137,107,140,120,134,70,136,79,81,146,123,95,127,150,53,112,154,90,148,
143,37,80,95,154,59,127,124,148,157,17,111,167,133,112,111,16,172,16,125,
147,112,169,170,179,38,103,159,176,191,81,134,136,89,153,113,185,4,199,178,
92,196,192,193,190,176,195,75,153,199,200,207,114,150,89,181,205,71,214,115,
74,210,219,120,222,41,217,218,206,154,157,84,134,211,226,233,68,217,197,107,
227,49,204,123,238,129,224,113,243,102,103,106,251,73,94,182,92,33,85,105,
224,147,123,252,12,242,18,240,79,97,67,131,15,125,140,17,49,110,34,150,
27,61,230,88,228,133,177,35,69,143,12,61,118,4,73,106,89,70,144,26,
42,133,120,251,55,207,162,198,143,20,107,156,228,40,243,162,74,146,43,89,
101,12,201,144,103,207,148,63,103,98,171,120,243,166,79,162,10,147,42,93,
106,48,4,0,33,206,8,104,105,110,116,45,108,105,116,0,33,249,4,1,
0,0,0,0,44,0,0,0,0,38,0,56,0,0,5,254,32,32,142,100,
105,158,104,170,174,108,27,189,240,219,206,192,43,221,248,45,211,168,157,255,
186,8,207,20,1,26,37,194,225,168,120,52,38,135,204,166,83,25,205,9,
174,130,41,175,122,195,122,179,191,167,235,247,253,134,105,220,114,249,60,198,
169,213,57,177,170,250,94,227,228,169,104,29,174,155,233,247,102,125,109,18,
128,129,72,126,110,88,17,2,139,141,139,88,119,136,93,88,3,101,149,144,
130,44,127,87,151,94,157,96,135,146,132,148,151,3,159,145,104,137,164,166,
134,120,43,155,2,166,172,152,161,80,170,178,94,168,84,155,184,160,59,74,
34,122,189,186,192,193,63,178,113,197,37,81,200,196,202,198,55,205,174,202,
76,205,181,207,193,17,6,6,178,3,219,191,216,53,4,4,219,219,5,5,
211,192,47,227,4,5,237,237,224,216,17,228,229,230,233,187,236,239,238,241,
207,243,245,246,225,150,204,203,231,14,221,61,124,236,248,5,140,161,48,96,
13,24,11,15,134,147,33,177,159,16,57,13,73,100,212,120,113,153,196,141,
217,106,20,171,72,241,201,175,146,38,51,99,188,42,41,146,226,195,139,41,
87,238,56,25,243,161,64,23,73,102,138,209,25,82,83,206,154,54,131,10,
157,243,179,101,71,158,48,69,18,189,217,147,38,83,135,80,163,74,157,58,
36,4,0,33,206,7,110,101,119,45,108,105,116,0,33,249,4,1,0,0,
0,0,44,0,0,0,0,38,0,56,0,0,5,254,32,32,142,100,105,158,
104,170,154,81,219,174,112,233,186,71,253,198,164,59,206,117,239,223,49,23,
98,22,65,248,142,61,96,138,134,236,33,158,80,232,79,213,66,70,159,86,
35,246,160,204,25,157,219,166,239,187,141,156,138,223,131,116,28,29,59,109,
102,89,186,13,198,174,183,233,184,72,88,63,134,181,100,53,101,122,104,115,
97,106,134,111,137,92,57,126,105,136,134,129,145,54,59,143,107,144,118,116,
150,88,64,69,117,120,87,151,155,95,132,160,161,167,115,108,164,149,100,168,
161,110,125,140,123,174,109,175,111,130,101,172,168,136,159,169,184,70,9,165,
135,170,170,128,125,193,94,143,142,142,151,188,7,200,172,98,184,203,212,208,
179,202,212,217,188,9,214,45,195,89,77,135,192,157,205,98,229,142,220,122,
0,133,210,177,204,79,193,234,236,237,152,145,82,214,215,244,189,182,207,234,
235,223,210,92,245,72,39,3,141,190,98,135,8,202,193,118,16,91,60,22,
6,15,182,83,200,226,156,196,129,93,146,49,188,136,15,34,64,137,20,81,
120,251,72,47,164,200,121,28,96,31,194,24,73,242,8,183,142,84,70,234,
123,169,18,199,58,62,98,104,102,180,201,163,6,205,120,254,108,66,36,162,
67,168,209,163,72,147,42,77,250,162,232,77,121,80,131,60,189,73,181,147,
153,166,65,151,196,193,74,181,43,87,28,55,184,18,186,186,53,235,153,178,
123,172,146,237,26,4,109,81,177,107,193,142,77,11,53,238,210,187,120,243,
234,221,11,35,4,0,33,206,8,113,117,105,116,45,108,105,116,0,33,249,
4,1,0,0,0,0,44,0,0,0,0,38,0,56,0,0,5,254,32,32,
142,100,105,158,104,170,174,108,235,190,112,44,207,116,109,223,64,164,239,60,
158,239,130,160,80,216,155,233,130,138,161,146,168,139,69,150,80,104,228,117,
20,38,163,203,38,235,185,188,98,135,218,84,21,234,37,131,85,220,104,89,
185,14,155,210,234,53,118,122,130,127,239,231,183,25,31,165,151,236,2,114,
124,68,122,67,130,124,11,11,65,126,35,112,135,119,137,138,139,133,131,66,
137,66,6,153,6,139,140,57,72,120,145,11,155,152,154,163,157,128,119,165,
164,154,2,110,34,17,143,74,165,153,65,179,173,157,57,94,180,81,179,163,
2,172,173,117,186,190,75,189,67,187,184,185,171,196,203,187,89,40,112,192,
197,170,191,213,147,117,146,181,204,199,206,180,190,201,57,161,137,219,188,204,
224,58,226,6,151,169,190,73,224,63,17,145,153,235,214,95,238,43,232,162,
60,79,206,106,193,91,59,72,240,48,20,232,147,130,119,84,210,36,89,24,
200,85,141,35,10,34,70,188,229,163,209,62,135,21,51,106,220,200,177,227,
27,70,24,111,184,9,169,17,161,192,128,175,59,252,104,9,179,15,31,157,
38,83,86,198,252,97,177,133,204,154,52,83,226,68,163,178,103,206,159,36,
79,234,28,202,210,39,192,161,57,97,210,140,57,211,37,202,148,76,119,6,
253,232,177,166,73,145,77,171,78,133,17,2,0,33,206,8,117,110,100,111,
45,108,105,116,0,33,249,4,1,0,0,0,0,44,0,0,0,0,38,0,
56,0,0,5,254,32,32,142,100,105,158,104,170,174,108,235,190,112,44,207,
180,24,221,248,93,159,120,226,255,184,221,232,246,43,2,117,181,136,113,233,
67,32,99,68,230,18,225,148,41,165,76,106,245,117,197,102,183,173,174,55,
251,84,137,199,83,112,234,140,54,82,35,43,229,227,33,157,219,191,240,117,
194,206,239,247,211,121,60,123,126,132,124,128,40,114,133,138,116,69,90,129,
36,137,139,133,141,142,38,145,146,126,148,149,144,131,152,132,63,90,111,37,
151,158,134,77,161,106,164,165,115,160,168,143,68,171,127,167,161,101,87,177,
119,179,180,156,63,177,154,186,187,188,158,190,155,192,193,146,173,174,130,75,
139,195,162,202,123,203,184,205,106,163,62,166,99,168,206,136,214,215,82,217,
101,60,182,178,105,180,143,122,198,140,110,174,230,107,17,84,193,228,196,46,
55,239,95,229,51,244,90,205,224,48,56,217,247,66,0,248,91,23,112,84,
142,32,5,119,240,75,8,137,29,195,33,14,31,10,140,104,16,162,13,56,
8,47,78,132,232,16,99,30,29,30,61,106,68,8,18,163,165,143,129,42,
144,168,68,185,81,228,201,141,22,91,162,116,153,49,230,147,149,26,97,222,
100,135,147,102,200,145,50,17,149,204,169,115,232,69,138,18,147,42,93,154,
48,4,0,59,};
const Gif_Record buttons_gif = { buttons_gif_data, 3624 };

static const unsigned char digits_gif_data[] = {
71,73,70,56,57,97,36,0,38,0,243,0,0,255,0,0,85,26,139,218,
112,214,210,105,30,112,128,144,255,165,0,255,255,0,0,205,0,205,0,0,
165,42,42,106,90,205,255,215,0,139,35,35,0,100,0,25,25,112,0,0,
0,33,249,4,1,0,0,4,0,44,0,0,0,0,36,0,38,0,0,3,
173,72,186,220,254,48,202,73,171,189,11,232,141,169,14,96,168,117,207,23,
8,104,10,142,164,2,128,104,24,198,1,208,190,244,160,239,176,80,119,56,
144,78,38,28,192,126,151,160,177,182,49,25,125,54,139,146,233,248,60,145,
30,33,182,116,140,102,141,222,72,48,44,14,128,165,167,45,228,117,174,140,
179,234,201,43,94,93,97,230,100,46,189,188,103,224,239,118,114,129,104,125,
25,131,110,135,107,105,121,138,109,18,111,136,142,143,139,95,133,126,93,147,
102,150,134,87,44,126,83,140,141,105,76,77,71,146,149,39,62,68,57,155,
13,108,75,41,42,102,167,132,67,68,182,161,110,115,59,60,84,45,159,68,
190,191,85,77,185,195,199,200,201,202,203,204,36,9,0,33,249,4,1,0,
0,2,0,44,0,0,0,0,36,0,38,0,0,3,141,40,186,220,254,48,
202,73,43,184,53,179,27,2,208,25,215,121,224,36,118,6,89,62,103,80,
4,233,183,110,192,232,22,111,60,43,39,254,186,48,85,73,228,179,1,117,
171,154,241,194,201,9,65,74,166,76,80,115,78,161,24,71,53,120,221,53,
182,72,175,246,248,20,47,192,101,51,149,220,85,163,219,230,183,250,203,158,
111,234,118,30,62,47,207,175,173,126,127,92,129,125,51,82,135,108,135,76,
22,70,54,78,141,29,112,99,62,148,56,48,6,152,153,152,105,44,144,158,
141,146,95,138,163,164,161,129,167,168,169,170,171,172,115,9,0,33,249,4,
1,0,0,2,0,44,0,0,0,0,36,0,38,0,0,4,162,80,200,73,
171,189,56,235,205,187,247,64,40,142,192,135,133,65,170,174,65,104,82,64,
122,204,52,189,150,111,60,179,171,221,230,43,132,112,40,84,29,126,159,88,
170,200,11,48,143,184,78,140,217,34,41,17,1,104,242,230,170,160,176,72,
105,170,155,153,134,57,34,49,54,250,218,40,217,237,178,243,28,183,124,233,
117,216,18,159,23,220,249,121,87,85,125,118,50,128,117,40,71,135,113,74,
80,112,132,141,139,140,134,143,144,148,104,100,110,70,85,86,86,146,19,102,
138,77,77,149,133,115,53,168,169,159,18,102,163,174,165,133,68,178,179,69,
176,166,174,163,182,94,157,188,36,132,191,192,193,194,195,196,197,29,17,0,
33,249,4,1,0,0,1,0,44,0,0,0,0,36,0,38,0,0,4,188,
48,200,73,171,189,56,235,205,187,255,1,32,142,36,136,137,73,170,174,162,
73,1,170,34,207,74,186,36,128,27,166,242,26,219,56,19,44,81,83,145,
120,192,220,7,86,188,41,37,195,154,115,137,156,86,152,73,15,246,22,180,
108,187,156,239,243,74,76,88,195,190,241,171,124,222,144,70,39,54,88,231,
149,207,233,208,168,249,174,27,253,218,120,67,68,69,124,116,48,11,10,92,
133,134,43,137,53,106,129,126,42,128,120,19,88,101,144,149,59,77,139,129,
156,153,149,151,148,94,111,160,155,89,110,105,25,162,157,150,114,166,172,166,
174,82,41,153,122,123,178,80,85,133,177,90,101,184,100,191,163,23,183,181,
71,194,181,84,131,62,63,123,173,196,49,52,51,64,207,39,130,204,70,185,
110,165,111,154,222,223,28,17,0,33,249,4,1,0,0,1,0,44,0,0,
0,0,36,0,38,0,0,4,163,48,200,73,171,189,56,235,205,123,5,128,
39,82,0,19,142,98,105,162,158,186,178,155,42,188,112,38,211,181,229,206,
103,254,49,140,2,131,231,251,1,133,196,226,196,133,196,249,84,165,102,239,
9,4,5,135,78,24,52,16,197,78,107,165,83,55,153,219,114,175,100,109,
117,137,206,166,214,108,105,217,57,118,119,204,113,175,58,91,255,222,225,63,
114,40,97,24,125,131,128,129,122,111,118,103,130,127,38,32,145,146,86,82,
147,26,46,64,153,154,153,77,155,126,108,65,5,162,163,164,164,67,2,168,
168,140,152,155,173,109,158,54,147,178,146,109,178,74,134,74,36,181,185,186,
142,188,184,188,103,154,159,79,182,193,44,17,0,33,249,4,1,0,0,1,
0,44,0,0,0,0,36,0,38,0,0,4,156,48,200,73,171,189,56,235,
205,187,247,64,40,142,100,248,81,0,163,174,108,11,156,83,58,204,116,77,
51,47,28,164,109,191,230,176,148,98,72,44,14,113,186,157,111,9,60,165,
74,80,147,238,153,4,33,171,28,42,118,243,140,54,147,188,165,74,10,102,
216,206,227,106,88,60,187,6,85,198,162,106,224,118,50,20,98,188,185,110,
197,65,225,123,95,29,34,24,60,120,116,130,91,74,135,124,138,18,60,136,
142,22,144,141,142,66,145,146,49,119,152,153,143,115,149,91,151,160,88,66,
129,157,139,166,157,97,156,150,50,109,137,83,33,159,105,106,35,61,132,161,
46,184,146,36,167,190,191,23,17,0,33,249,4,1,0,0,1,0,44,0,
0,0,0,36,0,38,0,0,4,199,48,200,73,107,24,56,99,203,123,197,
77,40,134,155,103,74,96,83,20,163,56,156,94,170,146,218,208,188,176,101,
55,192,92,82,191,28,42,212,99,225,132,167,93,241,134,132,41,125,151,90,
16,105,91,190,118,173,219,212,244,52,62,137,61,151,176,26,98,17,105,93,
146,243,108,230,105,39,160,37,147,203,62,31,129,110,243,93,231,158,245,246,
120,114,128,67,125,122,73,121,115,124,136,106,116,130,28,105,137,141,80,138,
142,107,86,143,117,145,49,136,131,144,131,124,151,148,101,154,29,100,70,165,
117,159,31,156,168,172,150,147,162,167,107,51,164,112,169,135,163,170,23,183,
116,180,186,187,174,152,190,57,105,157,163,181,173,97,111,40,59,134,77,74,
202,25,101,206,77,81,34,0,202,43,98,213,64,50,35,25,220,165,82,225,
228,229,230,231,232,233,234,66,17,0,33,249,4,1,0,0,1,0,44,0,
0,0,0,36,0,38,0,0,4,118,48,200,73,171,189,56,235,205,187,223,
64,40,142,100,41,114,128,163,174,108,235,58,0,234,12,116,109,223,54,44,
191,124,27,203,141,160,112,72,28,234,64,189,100,227,136,84,153,158,171,31,
104,212,73,49,63,30,171,20,187,219,114,155,222,111,70,43,238,150,205,231,
177,51,173,33,179,49,238,119,37,46,167,208,235,129,59,94,95,231,191,253,
127,107,120,19,128,108,133,105,135,101,137,138,130,131,121,141,142,139,95,86,
87,123,144,131,84,142,111,17,0,33,249,4,1,0,0,1,0,44,1,0,
0,0,35,0,38,0,0,4,177,48,200,73,39,184,248,214,205,249,101,96,
8,106,93,73,1,224,49,102,163,105,162,140,202,0,21,76,187,94,220,110,
54,94,235,134,89,78,232,179,232,136,195,91,17,165,50,40,121,187,37,16,
249,163,226,152,140,224,243,20,149,54,173,129,94,209,40,211,86,183,94,144,
89,34,30,115,203,194,182,251,173,158,205,208,115,246,49,8,206,135,97,112,
125,99,31,118,123,93,110,48,113,41,117,130,47,33,74,128,140,120,37,137,
91,145,89,135,142,125,151,107,87,153,70,83,141,92,162,88,152,147,103,46,
88,157,154,167,122,95,173,160,164,83,176,160,167,170,162,85,130,137,171,158,
153,187,184,67,119,44,152,192,29,132,34,34,36,126,108,25,205,203,207,208,
209,210,211,212,213,17,0,33,249,4,1,0,0,1,0,44,0,0,0,0,
36,0,38,0,0,4,197,48,200,73,171,189,56,235,205,49,248,32,208,117,
96,98,158,9,56,122,231,113,156,203,114,126,43,5,152,174,89,154,177,94,
7,183,196,43,37,146,124,96,190,81,112,88,172,220,94,178,20,9,151,188,
60,19,209,38,75,88,101,65,187,150,43,56,204,205,102,150,99,107,57,13,
92,107,207,107,169,250,251,246,98,217,87,89,125,206,75,231,229,27,104,102,
100,116,83,113,123,127,123,100,135,124,122,134,95,128,54,84,142,26,65,140,
141,145,106,92,119,153,19,130,157,158,119,67,148,91,133,100,81,144,138,161,
110,77,71,81,151,149,147,58,71,156,155,164,129,40,61,125,68,176,28,59,
40,62,137,63,70,33,42,127,160,195,70,189,201,146,169,195,52,78,199,170,
177,197,104,179,204,150,40,57,68,204,196,192,51,211,53,213,208,221,229,230,
231,232,23,17,0,59,};
const Gif_Record digits_gif = { digits_gif_data, 1946 };
