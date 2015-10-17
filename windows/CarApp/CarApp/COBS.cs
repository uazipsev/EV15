using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TegamHost
{
    class COBS
    {
        public static ushort Encode(byte[] input, ushort length, ref byte[] output)
        {
            ushort read_index = 0;
            ushort write_index = 1;
            ushort code_index = 0;
            byte code = 1;

            while(read_index < length)
            {
                if(input[read_index] == 0)
                {
                    output[code_index] = code;
                    code = 1;
                    code_index = write_index++;
                    read_index++;
                }
                else
                {
                    output[write_index++] = input[read_index++];
                    code++;
                    if(code == 0xFF)
                    {
                        output[code_index] = code;
                        code = 1;
                        code_index = write_index++;
                    }
                }
            }

            output[code_index] = code;

            return write_index;
        }

        public static ushort Decode(byte[] input, ushort length, ref byte[] output)
        {
            ushort read_index = 0;
            ushort write_index = 0;
            byte code;
            byte i;

            while(read_index < length)
            {
                code = input[read_index];

                if(read_index + code > length && code != 1)
                {
                    return 0;
                }

                read_index++;

                for(i = 1; i < code; i++)
                {
                    output[write_index++] = input[read_index++];
                }
                if(code != 0xFF && read_index != length)
                {
                    output[write_index++] = 0;
                }
            }

            return write_index;
        }
    }
}
