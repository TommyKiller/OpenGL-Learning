using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MyClassLibrary.Tasks
{
    public class Fix : ProjectTask
    {
        public string AdditionalInfo { get; }

        public Fix(string description, DateTime deadLine, string additionalInfo = "")
            : base(description, deadLine)
        {
            AdditionalInfo = additionalInfo;
        }
    }
}
