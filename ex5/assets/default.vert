#version 430

// Input attributes
layout(location = 0) in vec3 iPosition;
layout(location = 1) in vec3 iColor;
layout(location = 2) in vec3 iNormal;

// Output attributes
out vec3 v2fColor;
out vec3 v2fNormal;

// location = 0 in the original document
layout( location = 3 ) uniform mat4 uProjCameraWorld;
layout( location = 1 ) uniform mat3 uNormalMatrix;

void main()
{
    // Copy input color to the output color attribute
    v2fColor = iColor;
    v2fNormal = normalize(uNormalMatrix * iNormal);

    // Copy position to the built-in gl_Position attribute
    gl_Position = uProjCameraWorld * vec4( iPosition, 1.0 );
}