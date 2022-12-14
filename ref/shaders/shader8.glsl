//original https://www.shadertoy.com/view/wdlGRM

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{

    vec2 uv = (fragCoord.xy-iResolution.xy*.5)/iResolution.y;
	
    uv *= mat2(1., -1., 1., 1.);
    uv *= 80.;
    
    vec2 gv = fract(uv)-1.; 
	vec2 id = floor(uv) * 8.;
    
	float m = 0.;
    float t;
    for(float y=-1.; y<=1.; y++) {
    	for(float x=-1.; x<=1.; x++) {
            vec2 offs = vec2(x * .1, y * .1);
            
            t = -iTime+length(id-offs);
            float r = mix(.3, .5, tan(t*.6)*.2+.1);
    		float c = smoothstep(r, r, length(gv+offs));
    		m = m*(1.-c) + r*(2.-m);
        }
    }

    fragColor = vec4(m);
}