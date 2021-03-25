using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class timer_bomb : MonoBehaviour
{
    Transform transform2;
    float timer;
    float timealive;
    Animator anim;
    [SerializeField] GameObject bombcollider;
    // Start is called before the first frame update
    void Start()
    {
        transform2 = GetComponent<Transform>();
        anim = GetComponent<Animator>();
        timer = 2.3f;
        timealive = 2.7f;
    }

    // Update is called once per frame
    void Update()
    {
        timer -= Time.deltaTime;
        timealive -= Time.deltaTime;
        if (timer < 0)
        {
            var n = Instantiate(bombcollider, transform.position, Quaternion.Euler(0f, 0f, 0f));
            transform2.localScale *= 7;
            n.transform.parent = gameObject.transform;
            timer = 1f;
            anim.SetFloat("speed", 2);
        }
        if (timealive < 0)
        {
            Destroy(gameObject);
        }
    }

}
