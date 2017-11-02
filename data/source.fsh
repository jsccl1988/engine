varying vec3 normal;
varying vec3 l;

void main()
{
	float dp = dot(normalize(normal), normalize(l));
	float a = 0.2 + max(0.0, dp);
	gl_FragColor = vec4(a, 0.0, 0.0, 1.0);
}
