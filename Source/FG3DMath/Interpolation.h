#pragma once

class FInterpolation {
public:
	float LerpTime = 0.f;
	float Duration = 0.f;
	float CurrentValue = 0.f;
	float T = 0.f;

	void Initialize(const float LerpDuration) {
		Duration = LerpDuration;
		LerpTime = 0.f;
	}

	void Update(const float DeltaTime) {
		LerpTime += DeltaTime;
		FMath::Clamp(LerpTime, 0, Duration);
		T = LerpTime / Duration;
	}

	float GetValue() const {
		return CurrentValue;
	}

	bool Finished() const {
		return LerpTime >= Duration;
	}

	void Reset() {
		LerpTime = 0.f;
		CurrentValue = 0.f;
	}

	void EaseQuadInOut() {
		CurrentValue = T < 0.5 ? 2 * T * T : 1 - FMath::Pow(-2 * T + 2, 2) / 2;
	}
};
