//original https://www.shadertoy.com/view/3sSGWt

float HexDist(vec2 pos) {
    pos = abs(pos);
    
    float c = dot(pos, normalize(vec2(1,1.73)));
    c = max(c, pos.x);
    
    return c;
}

vec4 HexCoords (vec2 uv) {
    vec2 r = vec2(.2, .3);
    vec2 h = r*.1;
    vec2 a = mod(uv, r) - .2;
    vec2 b = mod(uv - h, .2) - h;
    
    vec2 gv;
    if(length(a) < length(b)) 
        gv = a;
    else
        gv = b;
        
    float x = atan(gv.x, gv.y);;
    float y = .8 - HexDist(gv);
    vec2 id = uv-gv;
        
    return vec4(x, y, id.x, id.y);   
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 uv = (fragCoord - 0.5*iResolution.xy) / iResolution.y;
    
    vec3 col = 0.7 + 0.3*sin(iTime+uv.xyx+vec3(2,1,4));
    
    uv *= 6.;
    
    vec4 hc = HexCoords(uv);
    float c = smoothstep(.4 * sin(hc.w+iTime), .7 * sin(hc.z+iTime), hc.y*sin(hc.z*hc.w+iTime));
    col += c * .6;
    
    fragColor = vec4(col, 1.0);
}