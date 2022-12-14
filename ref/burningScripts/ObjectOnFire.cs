using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectOnFire : MonoBehaviour
{
    bool isScaling = false;
    bool isBurned = false;
    float burnTime = 2f;
    Vector3 endSize = new Vector3(1, 1, 1);
    int treeChild = 3;

    public GameObject spawnPrefab;

    private void Start()
    {
        for (int i = 0; i < 3; i++)
        {
            transform.GetChild(i).gameObject.SetActive(false);
        }

        var children = gameObject.GetComponentsInChildren<Transform>();
    }

    IEnumerator ScaleOverTime(Transform objectToScale, Vector3 toScale, float duration )
    { 
        if (isScaling)
        {
            yield break;
        }
        isScaling = true;
        float counter = 0;
        Vector3 startScaleSize = objectToScale.localScale;

        StartCoroutine(showChildren());

        while (counter < duration)
        {
            gameObject.tag = "OnFire";
            counter += Time.deltaTime;
            GameObject child = transform.GetChild(treeChild).GetChild(0).gameObject;

            if (counter < burnTime)
            {
                child.GetComponent<Renderer>().material.color = Color.red;
            }
            else if (counter >= (burnTime) && counter < (burnTime * 2))
            {
                child.GetComponent<Renderer>().material.color = Color.yellow;
            }
            else if (counter >= (burnTime * 2))
            {
                child.GetComponent<Renderer>().material.color = Color.black;
            }

            objectToScale.localScale = Vector3.Lerp(startScaleSize, toScale, counter / duration);
            yield return null;
        }

        isScaling = false;
        StartCoroutine(showChildren());
        gameObject.tag = "NotOnFire";
    }

    IEnumerator waiter()
    {
        yield return new WaitForSeconds(1);
        StartCoroutine(ScaleOverTime(gameObject.transform, endSize, burnTime * 3));
    }

    IEnumerator showChildren()
    {
        transform.GetChild(0).gameObject.SetActive(isScaling);
        yield return new WaitForSeconds(0.5f);
        transform.GetChild(1).gameObject.SetActive(isScaling);
        yield return new WaitForSeconds(0.5f);
        transform.GetChild(2).gameObject.SetActive(isScaling);
    }

    private void OnCollisionStay(Collision collision)
    {
        if(!isBurned)
        {   
            if(collision.gameObject.CompareTag("OnFire"))
            {
                StartCoroutine(waiter());
                isBurned = true;
            }
        }
    }
}