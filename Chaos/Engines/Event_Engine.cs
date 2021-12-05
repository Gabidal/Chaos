using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;

namespace Chaos
{
    class Event : Entity
    {
        //The participating entities.
        public List<Entity> Participants;

        //The amount of power that is associated in this event.
        public double Significance => Participants.Sum(i => i.Power);

        //This describes how this event affects the relationships of the participants.
        public double Grade;    //-1..1
    }

    class Event_Engine
    {

    }
}
