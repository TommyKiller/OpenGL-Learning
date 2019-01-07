using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MyClassLibrary.Tasks
{
    public class FixBug : ProjectTask
    {
        public FixBug(string description, DateTime deadLine)
            : base(description, deadLine)
        {

        }
    }
}
