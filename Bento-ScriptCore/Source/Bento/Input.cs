using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bento
{
    public class Input
    {
        public static bool GetKey(KeyCode keyCode)
        {
            return InternalCalls.Input_IsKey(keyCode);
        }

        public static bool GetKeyDown(KeyCode keyCode)
        {
            return InternalCalls.Input_IsKeyDown(keyCode);
        }
    }
}
