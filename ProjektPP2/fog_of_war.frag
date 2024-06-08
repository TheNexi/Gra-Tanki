#version 330 core

uniform vec2 circlePosition;
uniform float circleRadius;

void main() {
//circlePosition.y= -circlePosition
    vec2 fragPosition = gl_FragCoord.xy;
    float distance = length(fragPosition - circlePosition);
    
    if (distance < circleRadius) {
        gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0); // Przezroczystość wewnątrz okręgu
    } else {
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0); // Czarna mgła na zewnątrz okręgu
    }
}
