using System;
using System.Collections;
using System.Diagnostics.SymbolStore;
using System.IO;
using System.Reflection;
using System.Runtime.CompilerServices;


namespace Bento
{
    public class Entity
    {
        protected Entity() { ID = 0; }

        internal Entity(ulong id)
        {
            ID = id;
        }
        public readonly ulong ID;
        
        public Transform transform
        {
            get { return GetComponent<Transform>(); }
        }

        public string name
        {
            get { InternalCalls.Entity_GetName(ID, out string name); return name; }
        }
        public bool HasComponent<T>() where T : Component, new()
        {
            Type componentType = typeof(T);
            return InternalCalls.Entity_HasComponent(ID, componentType);
        }
        public T GetComponent<T>() where T : Component, new()
        {
            if (!HasComponent<T>())
                return null;

            T component = new T() { entity = this };
            return component;
        }

    }
}