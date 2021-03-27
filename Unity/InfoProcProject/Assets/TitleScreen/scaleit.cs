using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class scaleit : MonoBehaviour
{
    float timer = 0.5f;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (timer > 0)
        {
            timer -= Time.deltaTime;
        }
        else
        {
            timer = 0.5f;
            gameObject.transform.localScale *= 5;
        }
    }
}
