using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MyClassLibrary
{
    public abstract class ProjectTask
    {
        public ProjectTaskStatus Status { get; set; }
        public string Description { get; set; }
        public DateTime DeadLine { get; }

        public ProjectTask(string description, DateTime deadLine)
        {
            Status = ProjectTaskStatus.Queued;
            Description = description;
            DeadLine = deadLine;
        }
    }
}
