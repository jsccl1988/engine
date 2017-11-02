/* Texture slots */
uniform sampler2D grass1;
uniform sampler2D grass2;
uniform sampler2D grass3;

/* Splatting map */
uniform sampler2D map;

/* Scaling parameters */
/* They are used to scale splatting map up to size of the terrain */
uniform float w_scale;
uniform float h_scale;

void main()
{
  /* Request data of the base textures */
  vec3 color1 = texture2D(grass1, gl_TexCoord[0].st).rgb;
  vec3 color2 = texture2D(grass2, gl_TexCoord[0].st).rgb;
  vec3 color3 = texture2D(grass3, gl_TexCoord[0].st).rgb;

  /* Request data of the splatting map */
  vec3 mapData = texture2D(map, vec2(gl_TexCoord[0].s / w_scale, gl_TexCoord[0].t / h_scale)).rgb;

  float a = 1.0 - mapData.r - mapData.g;

  /* This check is needed because I've used gradient map intead of correct splatting map */
  if (a < 0.0) 
  {
    a = 0.0;
  }

  /* Compute resulted color */
  gl_FragColor = vec4(color1 * mapData.r + color2 * mapData.g + color3 * a, 1.0);
}
