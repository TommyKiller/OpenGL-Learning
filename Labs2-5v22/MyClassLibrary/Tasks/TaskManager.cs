using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MyClassLibrary
{
    public static class TaskManager
    {
        public static void StartTask(ProjectTask Task)
        {
            Task.Status = ProjectTaskStatus.InWork;
        }

        public static void EndTask(ProjectTask Task)
        {
            Task.Status = ProjectTaskStatus.Completed;
        }

        public static void StopTask(ProjectTask Task)
        {
            Task.Status = ProjectTaskStatus.Queued;
        }

        public static void CancelTask(ProjectTask Task)
        {
            Task.Status = ProjectTaskStatus.Impracticable;
        }
    }
}
