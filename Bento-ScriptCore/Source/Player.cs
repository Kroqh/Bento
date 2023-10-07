using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Bento;

namespace Sandbox
{
    public class Player : Entity
    {

        Rigidbody2D rb;
        public float jumpHeight = 2.0f;
        float gravity = -9.82f;
        void OnCreate()
        {
            Console.WriteLine($"Name: {name} \n UUID: {ID}");
            rb = GetComponent<Rigidbody2D>();
            
        }

        void OnUpdate(float ts)
        {

            float speed = 5.0f;
            Vector3 velocity = Vector3.zero;


            if (Input.GetKey(KeyCode.D))
                velocity.x += 1;
            if (Input.GetKey(KeyCode.A))
                velocity.x -= 1;

            velocity.Normalize();
            velocity *= speed;
            velocity += new Vector3(0, rb.velocity.y, 0);

            if (Input.GetKeyDown(KeyCode.Space))
                velocity.y = (float)Math.Sqrt(jumpHeight * -2f * gravity);

            rb.velocity = velocity;


        }
    }
}
