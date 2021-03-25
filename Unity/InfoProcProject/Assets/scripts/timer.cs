using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class timer : MonoBehaviour
{
    public float time;
    // Start is called before the first frame update
    void Start()
    {
        time = 0.02f;
    }

    // Update is called once per frame
    void Update()
    {
        if (time > 0)
        {
            time -= Time.deltaTime;
        }
        else
        {
            Destroy(gameObject);
        }
    }
}
