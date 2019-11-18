#pragma once

#include "Camera.h"

class HorizontalScroll
{
public:
	HorizontalScroll();

	void Update();

	Camera* GetCam() const;
	Transform* GetFocus() const;
	float GetOffset() const;

	void SetCam(Camera* cam);
	void SetFocus(Transform* focus);
	void SetOffset(float offset);
private:
	Camera* m_cam = nullptr;
	Transform* m_focus = nullptr;

	float m_offset = 5.f;
};

inline void from_json(const nlohmann::json& j, HorizontalScroll& horiScroll)
{
	horiScroll.SetOffset(j["Offset"]);
}

inline void to_json(nlohmann::json& j, const HorizontalScroll& horiScroll)
{
	j["Offset"] = horiScroll.GetOffset();
}