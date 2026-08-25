#type vertex

#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 v_Normal;
out vec2 v_TexCoord;

void main()
{
    gl_Position =
        u_Projection *
        u_View *
        u_Model *
        vec4(a_Position, 1.0);

    mat3 normalMatrix =
        transpose(
            inverse(
                mat3(u_Model)
            )
        );

    v_Normal =
        normalize(
            normalMatrix *
            a_Normal
        );

    v_TexCoord =
        a_TexCoord;
}

#type fragment

#version 460 core

in vec3 v_Normal;
in vec2 v_TexCoord;

uniform vec4 u_Color;

uniform vec3 u_LightDirection;
uniform vec3 u_LightColor;

uniform sampler2D u_AlbedoTexture;
uniform int u_HasAlbedoTexture;

out vec4 FragColor;

void main()
{
    vec3 normal =
        normalize(v_Normal);

    vec3 lightDirection =
        normalize(-u_LightDirection);

    float diffuse =
        max(
            dot(
                normal,
                lightDirection
            ),
            0.0
        );

    vec3 ambient =
        0.15 *
        u_LightColor;

    vec3 lighting =
        ambient +
        diffuse *
        u_LightColor;

    vec4 albedo =
        u_Color;

    if (u_HasAlbedoTexture == 1)
    {
        albedo *=
            texture(
                u_AlbedoTexture,
                v_TexCoord
            );
    }

    FragColor =
        vec4(
            albedo.rgb *
            lighting,
            albedo.a
        );
}