//original https://www.shadertoy.com/view/wdlGRM

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{

    vec2 uv = (fragCoord.xy-iResolution.xy*.5)/iResolution.y;
	
    uv *= mat2(1., -1., 1., 1.);
    uv *= 200.;
    
    vec2 gv = fract(uv) + sin(iTime); 
	vec2 id = floor(uv) * cos(gv.x/2.);
    
	float m = 0.;
    float t;
    for(float y=-1.; y<=1.; y++) {
    	for(float x=-1.; x<=1.; x++) {
            vec2 offs = vec2(x * 100., y * 1.);
            
            t = -iTime+length(id-offs);
            float r = smoothstep(.2, .002, tan(t*.1)*.2+.8);
    		float c = smoothstep(tan(r * .001), r, length(gv+offs));
    		m = m*(.02-c) + r*(.8-m);
        }
    }

    fragColor = vec4(m);
}