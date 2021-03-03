using System;
using System.Collections.Generic;
using System.Text;

namespace Chaos
{
    class Relation
    {
        public Entity Friend;

        public double Relationship; // -1..1

        public Relation(Entity entity, double relationship = 0)
        {
            Friend = entity;
            Relationship = relationship;
        }
    }

    class Environment
    {
        //Parent features
        public List<Relation> Neighbours;

        //allies features
        public Relation Parent;

        //If certain entity is inside power radious, it is count as non independent entity.

        //TODO!!! What happends when there is a child entity between a shared area.
    }

    class Entity
    {
        //The position in the world
        public Vector Position;

        //Radios of the area that this entity has
        public double Power;

        //This inlists all close-by entities and its relationship between them.
        public Environment Environment;

        //The movement speed.
        public double Speed;

        //These function pointters are user defined function that tells the entity what to do in sertain situations.
        //The behaviour of the entity during a event
        public Action<Entity, Event, World> Event_Handler;

        //Use case: if (a.Governs(b)) {..}
        //Calculate if another entity is inside this entity
        public bool Governs(Entity entity)
        {
            double delta_x = entity.Position.X - Position.X;
            double delta_y = entity.Position.Y - Position.Y;
            double delta_z = entity.Position.Z - Position.Z;
            double Distance = Math.Sqrt(delta_x * delta_x + delta_y * delta_y + delta_z * delta_z);

            //If the distance between this entity and the other is greater than the governed radius, then return false. If not then, return true
            return Distance < Power;
        }


    }
}
