//original https://www.shadertoy.com/view/cs2Szm

float rand (vec2 n) { 
	return fract(tan(dot(n, vec2(12.9898, 4.1414))) * 43758.5453);
}

vec2 rotate (vec2 v, float a) {
	float s = sin(a);
	float c = cos(a);
	mat2 m = mat2(c, -s, s, c);
	return m * v;
}

void mainImage( out vec4 fragColor, in vec2 fragCoord ) {
    vec2 coord = 2.5 * fragCoord.xy / iResolution.xy;

    for(int n = 1; n < 125; n++){
        float i = float(n);
        coord += vec2(.2 / i * cos(10. * coord.y + iTime + .2 * i) + 8., 2.4 / i * sin(coord.x + iTime + 0.2 * i) + 100.6);
    }

    vec3 color = vec3(1.5 * sin(coord.x) + .7, .8 * sin(coord.y * .2) + .9, tan(coord.x + coord.y));


    fragColor = vec4(color, 1.0);
}
