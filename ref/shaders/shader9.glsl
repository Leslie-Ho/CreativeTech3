//original https://www.shadertoy.com/view/wdlGRM

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{

    vec2 uv = (fragCoord.xy-iResolution.xy*.5)/iResolution.y;
	
    uv *= mat2(1., -1., 1., 1.);
    uv *= 50.;
    
    vec2 gv = fract(uv)-.5; 
	vec2 id = floor(uv) * tan(.2);
    
	float m = 0.;
    float t;
    for(float y=-1.; y<=1.; y++) {
    	for(float x=-1.; x<=1.; x++) {
            vec2 offs = vec2(x * 5., y * .1);
            
            t = -iTime+length(id-offs);
            float r = mix(.3, .05, tan(t*.6)*.2+.08);
    		float c = smoothstep(r, r, length(gv+offs));
    		m = m*(1.-c) + r*(1.-m);
        }
    }

    fragColor = vec4(m);
}