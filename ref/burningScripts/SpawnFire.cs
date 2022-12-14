using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpawnFire : MonoBehaviour
{
    public GameObject firePrefab;

    void Update()
    {
        var pos = Random.insideUnitSphere * 10f + transform.position;
        pos.y = 100;
        if (Input.GetKeyDown(KeyCode.Space))
        {
            Instantiate(firePrefab, pos, Quaternion.identity);
        }
    }

    private void OnBecameInvisible()
    {
        Destroy(firePrefab);
    }
}
