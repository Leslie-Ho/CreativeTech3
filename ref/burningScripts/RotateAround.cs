using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RotateAround : MonoBehaviour
{
    public int position;
    float wait;

    /* speed of orbit (in degrees/second) */
    float speed = 120;

    public void Update()
    {
        changeStartTime();
        StartCoroutine(waiter());
    }

    IEnumerator waiter()
    {
        yield return new WaitForSeconds(wait);
        this.transform.RotateAround(this.transform.parent.position, Vector3.up, speed * Time.deltaTime);
    }

    void changeStartTime()
    {
        switch (position)
        {
            case 1:
                wait = 0f;
                break;
            case 2:
                wait = 0.25f;
                break;
            case 3:
                wait = 0.5f;
                break;
            default:
                break;

        }
    }
}
