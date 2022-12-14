using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpawnObjects : MonoBehaviour
{
    public GameObject[] myObjects;
    public int numObjectsSpawned;
    int randomIndex;

    public GameObject terrain;


    // Start is called before the first frame update
    void Start()
    {
        
        SpawnPrefab();
    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Return))
        {

            //for (int i = 0; i < numObjectsSpawned; i++)
            //{
            //    int randomIndex = Random.Range(0, myObjects.Length);
            //    Vector3 randomSpawnPosition = new Vector3(Random.Range(-25, 25), 2, Random.Range(-25, 25));

            //    Instantiate(myObjects[randomIndex], randomSpawnPosition, Quaternion.identity);
            //}
            SpawnPrefab();
        }
    }

    void SpawnPrefab()
    {
        terrain.GetComponent<TerrainCollider>().enabled = true;
        if(numObjectsSpawned > 0)
        {
            for (int i = 0; i < numObjectsSpawned; i++)
            {
                var pos = Random.insideUnitSphere * 200f + transform.position;
                pos.y = 10 + transform.position.y;
                randomIndex = Random.Range(0, myObjects.Length - 1);

                RaycastHit hit;
                if (Physics.Raycast(pos, Vector3.down, out hit, 100) && hit.transform.tag == "Terrain")
                {
                    //Debug.Log("yes");
                    Instantiate(myObjects[randomIndex], hit.point, Quaternion.identity);

                }
            }

            terrain.GetComponent<TerrainCollider>().enabled = false;
        } 
    }
}
