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
    vec2 coord = 2.9 * fragCoord.xy / iResolution.xy;

    for(int n = 1; n < 200; n++){
        float i = float(n);
        coord += vec2(2.7 / i * tan(.4 * coord.y + iTime/2.), .4 / i * sin(coord.x + iTime / 2.));
    }

    vec3 color = vec3(2.2 * sin(coord.x) + .3, .8 * sin(coord.y * 2.2) + .9, tan(coord.x + coord.y));


    fragColor = vec4(color, 1.0);
}