#pragma once
#include <string>
#include <memory>

#ifdef WIN32 
#	include "RenderDX.h"
using render = egui::RenderDX;
#else 
#	include "RenderGL.h"
using render = egui::RenderGL;
#endif

namespace egui {
	class UIApp {
	public:
		static std::unique_ptr<UIApp> Create(const std::string resource);
		static void Release(std::unique_ptr<UIApp>&& ptr);
	protected:
		UIApp() {}
		~UIApp() {}
	};

	//controls
	class UIDialog {
		
	protected:
		virtual void render() = 0;

	};

		class UIAnimation {};
		class UIControl {}; 
			class UIContainer {}; 
				class UIHView {}; class UIVView {}; class UIGridView {}; class UIScrollView {};
			class UIText {};
				class UIImage {};
				class UIEditor {};
				class UISlider {};
				class UIScroll {};
				class UIButton {};
				class UICheckbox {};




}
