#include "shared.h"

DWORD game_mp;

extern cvar_t* g_bounce;

void G_PM_ClipVelocity(vec3_t in, vec3_t normal, vec3_t out) {
	float	backoff;
	float	change;
	int		i;
	float   overbounce = 1.001f;

	backoff = DotProduct(in, normal);

	if (backoff < 0) {
		backoff *= overbounce;
	}
	else {
		backoff /= overbounce;
	}

	for (i = 0; i < 3; i++) {
		change = normal[i] * backoff;
		out[i] = in[i] - change;
	}
}

// xoxor4d
void G_PM_ProjectVelocity(vec3_t in, vec3_t normal, vec3_t out) {
	float speedXY, DotNormalXY, normalisedNormalXY, projectionZ, projectionXYZ;

	speedXY = in[1] * in[1] + in[0] * in[0];

	if ((normal[2]) < 0.001f || (speedXY == 0.0f)) {
		VectorCopy(in, out);
	}
	else {
		DotNormalXY = normal[1] * in[1] + in[0] * normal[0];
		normalisedNormalXY = -DotNormalXY / normal[2];

		projectionZ = in[2] * in[2] + speedXY;

		projectionXYZ = sqrtf((projectionZ / (speedXY + normalisedNormalXY * normalisedNormalXY)));

		if (projectionXYZ < 1.0f || normalisedNormalXY < 0.0f || in[2] > 0.0f) {
			out[0] = projectionXYZ * in[0];
			out[1] = projectionXYZ * in[1];
			out[2] = projectionXYZ * normalisedNormalXY;
		}
	}
}

uint32_t G_PM_Bounce(vec3_t in, vec3_t normal, vec3_t out) {
	if (g_bounce->integer) {
		G_PM_ProjectVelocity(in, normal, out);
	}
	else {
		G_PM_ClipVelocity(in, normal, out);
	}

	return GAME_OFF(0x2000D570);
}

__declspec(naked) void G_PM_Bounce_Stub()
{
	__asm
	{
		push    esi; // out
		push    ecx; // normal
		push    edx; // in
		call    G_PM_Bounce;
		add     esp, 12;

		push eax
			retn;
	}
}

void G_Init(DWORD base) {
	game_mp = base;
	__jmp(GAME_OFF(0x2000D56B), (int)G_PM_Bounce_Stub);
}