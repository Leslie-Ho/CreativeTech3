//original https://www.shadertoy.com/view/wdlGRM
void mainImage( out vec4 fragColor, in vec2 fragCoord )
{

    vec2 uv = (fragCoord.xy-iResolution.xy*.5)/iResolution.y;
	
    uv *= mat2(.707, -.707, .707, .707);
    uv *= 20.;
    
    vec2 gv = fract(uv)-.2; 
	vec2 id = floor(uv);
    
	float m = 0.;
    float t;
    for(float y=-1.; y<=1.; y++) {
    	for(float x=-1.; x<=1.; x++) {
            vec2 offs = vec2(x, y);
            
            t = -iTime+length(id-offs);
            float r = mix(.01, .5, tan(t*.6)*.2+.1);
    		float c = smoothstep(r, r, length(gv+offs));
    		m = m*(1.-c) + c*(1.-m);
        }
    }

    fragColor = vec4(m);
}