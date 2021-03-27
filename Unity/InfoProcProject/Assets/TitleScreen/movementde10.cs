using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class movementde10 : MonoBehaviour
{

    private Vector3 initialPosWorld;
    private float speed = 20f;
    private float timer = 4;
    public bool canbeseen = false;
    // Start is called before the first frame update
    void Start()
    {
        initialPosWorld = transform.position;
        transform.position = new Vector3(transform.transform.position.x, transform.transform.position.y + 1 * 5.95f, transform.transform.position.z);
    }

    // Update is called once per frame
    void Update()
    {
        if (transform.position.y > initialPosWorld.y && canbeseen == true)
        {
            transform.position = new Vector3(transform.transform.position.x, transform.transform.position.y - Time.deltaTime * speed, transform.transform.position.z);
        }
    }
}
