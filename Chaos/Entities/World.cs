using System;
using System.Collections.Generic;
using System.Text;

namespace Chaos
{
    class World
    {
        //list of all entities in the world
        public List<Entity> Entities;

        //list of all events occuring in this world
        public List<Event> Events;
    }
}
