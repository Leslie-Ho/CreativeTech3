//original https://www.shadertoy.com/view/cs2Szm

float rand (vec2 n) { 
	return fract(tan(dot(n, vec2(12.9898, 4.1414))) * 43758.5453);
}

vec2 rotate (vec2 v, float a) {
	float s = tan(a);
	float c = tan(a);
	mat2 m = mat2(c, -s, s, c);
	return m * v;
}

void mainImage( out vec4 fragColor, in vec2 fragCoord ) {
    vec2 coord = 20.9 * fragCoord.xy / iResolution.xy;

    for(int n = 1; n < 2; n++){
        float i = float(n);
        coord += vec2(2.7 / i * tan(.04 * coord.x + iTime/2.), .04 / i * sin(coord.x + iTime / 2.));
    }

    vec3 color = vec3(2. * sin(coord.x) + .3, 2.8 * sin(coord.y * 2.2) + .009, tan(coord.x + coord.y));


    fragColor = vec4(color, 1.0);
}