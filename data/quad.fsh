/* Texture slots */
uniform sampler2D content;

void main()
{
  vec3 color = texture2D(content, gl_TexCoord[0].st).rgb;
  gl_FragColor = vec4(color, 1.0);
}
