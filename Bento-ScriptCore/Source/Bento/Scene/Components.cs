using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bento
{
    public abstract class Component
    {
        public Entity entity { get; internal set; }
    }

    public class Transform : Component
    {
        public Vector3 position
        {
            get
            {
                InternalCalls.TransformComponent_GetPosition(entity.ID, out Vector3 position);
                return position;
            }
            set
            {
                InternalCalls.TransformComponent_SetPosition(entity.ID, ref value);
            }
        }

        // TODO: Make rotation a quaternion
        public Vector3 rotation
        {
            get
            {
                InternalCalls.TransformComponent_GetRotation(entity.ID, out Vector3 rotation);
                return rotation;
            }
            set
            {
                InternalCalls.TransformComponent_SetRotation(entity.ID, ref value);
            }
        }
        public Vector3 localScale
        {
            get
            {
                InternalCalls.TransformComponent_GetLocalScale(entity.ID, out Vector3 scale);
                return scale;
            }
            set
            {
                InternalCalls.TransformComponent_SetLocalScale(entity.ID, ref value);
            }
        }
    }

    public enum ForceMode
    {
        Force,
        Impulse,
    }
    public class Rigidbody2D : Component
    {
        
        public Vector3 velocity
        {
            get
            {
                InternalCalls.Rigidbody2DComponent_GetVelocity(entity.ID, out Vector3 velocity);
                return velocity;
            }
            set
            {
                InternalCalls.Rigidbody2DComponent_SetVelocity(entity.ID, ref value);
            }
        }

        // Impuls not working
        public void AddForce(Vector3 forceDirection, ForceMode forceMode)
        {
            switch (forceMode)
            {
                case ForceMode.Force:
                    InternalCalls.Rigidbody2DComponent_AddForce_Force(entity.ID, ref forceDirection);
                    break;
                case ForceMode.Impulse:
                   
                    InternalCalls.Rigidbody2DComponent_AddForce_Impulse(entity.ID, ref forceDirection);
                    break;
                default:
                    break;
            }
        }
    }
}
