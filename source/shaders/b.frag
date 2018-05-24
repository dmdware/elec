""
"#version 120\r\n"
"#extension GL_EXT_gpu_shader4 : enable\r\n"
"varying vec3 ip;"
"uniform vec3 partp[4];"
"uniform float partq[4];"
"uniform float partm[4];"
"int trace3(vec3 dir, vec3 pos, float step)"
"{"
"	int i; int neari = -1; float neard;"
"	if(step >= 2)\r\n"
"	{"
"	//	gl_FragColor = vec4(0,1,0,1);	gl_FragDepth = step / 20.0; return 1;\r\n"
"	}\r\n"
"	for(i=0; i<4; ++i)"
"	{"
"		vec3 del = pos - partp[i];"
"		float d = sqrt((del.x*del.x+del.y*del.y+del.z*del.z));"
"		if( d < partm[i] * 0.001 && (neari < 0 || neard > d))\r\n"
"		{"
"			if(partq[i] == 0)\r\n{	gl_FragColor = vec4(0.5f,0.5f,0.5f,1) / (step*step*1.1) + vec4(0,0,0,1); }\r\n"
"			else if(partq[i] < 0){	gl_FragColor = vec4(1.0f,1.0f,0.5f,1) / (step*step*1.1) + vec4(0,0,0,1); }\r\n"
"			else\r\n"
"				{	gl_FragColor = vec4(0.0f,0.0f,1.0f,1) / (step*step*1.1) + vec4(0,0,0,1); }\r\n"
"			gl_FragDepth = step / 20.0;"
"			neari = i; neard = d;"
"		}"
"	}"
"	if(neari >= 0){ return 1; }"
"	return 0;"
"} //*/\r\n"
"void main()"
"{"
"	vec3 p3 = vec3(ip.x * 1 - 0.5, ip.y * 1 - 0.5, 0.1f);\r\n"
"	//gl_FragColor = vec4(1,0,0,1); gl_FragDepth = 0.5;\r\n"
"	float step;\r\n"
"	gl_FragColor = vec4(0,0,0,1);"
"	for(step = 0; step < 2; step += 1.0 / 200.0)\r\n"
"	{"
"		if(trace3(normalize(p3), vec3(0,0,0) + normalize(p3) * step, step) == 1)"
"			break;"
"	}"
"	//gl_FragColor = vec4(vec3(1,0,0), 0.06*(1.0 - gl_FragCoord.z)*(1.0 - gl_FragCoord.z));//vec4(gl_FragCoord.xyz/2.0 + vec3(0.5, 0.5, 0.0), 0.5 + (0.5 - gl_FragCoord.z/2.0) );\r\n"
"}"
""