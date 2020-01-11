/*
This sample code is from my Power Tower project, 
a 2-4 competitive multiplayer game student project.

This is part of the level object pooling system, 
where level chunks are randomly selected and stacked on top of each other.

by Czarina Ramos
*/
    
    public void UseChunk(List<GameObject> myList)
    {
        //grabs a random gameobject from the list and adds it to the 'currently using' List
        GameObject temp = myList[Random.Range(0, myList.Count)];
        myList.Remove(temp);
        chunksBeingUsed.Add(temp);
        //makes it a child of the main gameobject used for the level
        temp.transform.SetParent(LevelInput.transform);
        //shows it in the level
        temp.SetActive(true);

        //checks if there is no level chunk present
        //it being the first level chunk being used
        if (LevelInput.childCount <= 1)
        {
            //had to hardcode the position to (0, 0, 0) because of dependancy issues --
            //most of the game's functionality was dependant on this location
            temp.transform.localPosition = new Vector3(0, 0, 0); //also Vector3.Zero
            return;
        }

        temp.transform.localPosition = LevelInput.GetChild(LevelInput.childCount - 2).localPosition + new Vector3(0, levelHeight, 0);
    }

    public void RemoveChunk(List<GameObject> myList)
    {
        //removes the first thing on the list, because first in, first out (FIFO)
        GameObject temp = chunksBeingUsed[0];
        chunksBeingUsed.Remove(temp);
        myList.Add(temp);
        //makes it a child of the main gameobject used for storing level chunks
        temp.transform.SetParent(objectPool.transform);
        //organizes visually for debugging
        temp.transform.localPosition = objectPool.localPosition + new Vector3(0, levelHeight, 0);
        //hides it in the level
        temp.SetActive(false);
    }