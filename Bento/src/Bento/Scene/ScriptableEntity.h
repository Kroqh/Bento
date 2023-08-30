#pragma once
#include "Entity.h"

namespace Bento {

	class ScriptableEntity {

	public:
		virtual ~ScriptableEntity() {};
		template<typename T>
		T& GetComponent() {
			return m_Entity.GetComponent<T>();
		}

	protected:
		virtual void OnCreate() = 0;
		virtual void OnDestroy() = 0;
		virtual void OnUpdate(Bento::Timestep ts) = 0;
	private:
		Entity m_Entity;
		friend class Scene;

	};

}