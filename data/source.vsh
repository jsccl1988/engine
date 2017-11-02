varying vec3 normal;
varying vec3 l;

void main()
{
	normal = normalize(gl_Normal);
	vec3 lightPos = vec3(-10, -60, 40);
	l = normalize(lightPos - vec3(gl_ModelViewMatrix * gl_Vertex));
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
