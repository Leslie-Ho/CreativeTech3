//original https://www.shadertoy.com/view/3sSGWt

float HexDist(vec2 pos) {
    pos = abs(pos);
    
    float c = dot(pos, normalize(vec2(1,1.73)));
    c = max(c, pos.x);
    
    return c;
}

vec4 HexCoords (vec2 uv) {
    vec2 r = vec2(2., .2) + 5.;
    vec2 h = r * sin(3.);
    vec2 a = mod(uv, r);
    vec2 b = mod(uv - h, .01) - h;
    
    vec2 gv;
    if(length(a) < length(b)) 
        gv = a;
    else
        gv = b;
        
    float x = atan(gv.x, gv.y);;
    float y = .1 - HexDist(gv);
    vec2 id = uv-gv;
        
    return vec4(x, y, id.x, id.y);   
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 uv = (fragCoord - 0.5*iResolution.xy) / iResolution.y;
    
    vec3 col = vec3(0);
    
    uv = abs(uv);
    uv *= 20.;
    
    vec4 hc = HexCoords(uv);
    float c = smoothstep(.2 * tan(hc.w+iTime), 2. * tan(hc.z+iTime), cos(hc.z*hc.w+iTime));
    col += c;
    
    fragColor = vec4(col, 1.0);
}