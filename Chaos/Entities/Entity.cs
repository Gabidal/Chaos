using System;
using System.Collections.Generic;
using System.Text;

namespace Chaos
{
    class Environment
    {
        //Parent features
        public List<Entity> Neighbours;


        //allies features
        public Entity Parent;

        //both
        public double Relation; // -1..1

        //If certain entity is inside power radious, it is count as non independent entity.

        //TODO!!! What happends when there is a child entity between a shared area.
    }

    class Entity
    {
        //The position in the world
        public Vector Position;

        //
        public double Power;

        //This inlists all close-by entities and its relationship between them.
        public Environment Environment;

        //This is iver written by user defined function that tell the entity what to do in sertain situations.
        public Action<Entity, Event, World> Event_Handler;
    }
}
