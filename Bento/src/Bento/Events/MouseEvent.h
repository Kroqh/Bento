#pragma once
#include "Bentopch.h"
#include "Event.h"

namespace Bento {

	class MouseMovedEvent : public Event {
	
	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override {

			std::stringstream ss;

			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;

			return ss.str();

		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_MouseX;
		float m_MouseY;
		
	};

	class MouseScrolledEvent : public Event {

	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override {

			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();

		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryInput)

	private:
		float m_XOffset;
		float m_YOffset;

	};

	class MouseButtonEvent : public Event {

	public:
		inline int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		MouseButtonEvent(int mouseButton)
			: m_Button(mouseButton) {}

		int m_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent {

	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override {

			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_Button;
			return ss.str();

		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent {

	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override {

			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_Button;
			return ss.str();

		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}