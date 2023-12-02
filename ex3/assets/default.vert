#version 430

// Input attributes
layout(location = 0) in vec3 iPosition;
layout(location = 1) in vec3 iColor;

// Output attributes
out vec3 v2fColor;

// location = 0 in the original document
layout( location = 3 ) uniform mat4 uProjCameraWorld;

void main()
{
    // Copy input color to the output color attribute
    v2fColor = iColor;

    // Copy position to the built-in gl_Position attribute
    gl_Position = uProjCameraWorld * vec4( iPosition, 1.0 );
}