using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class bullet : MonoBehaviour
{
    Rigidbody2D rigid;
    float timer;
    [SerializeField] float speed = 20f;
    // Start is called before the first frame update
    float time = 1f;
    void Start()
    {
        rigid = GetComponent<Rigidbody2D>();
        Vector3 vec = transform.right * speed;
        vec.z = 0;
        rigid.velocity = vec;
        timer = 3f;
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
            Destroy(gameObject);
        }
    }
    private void OnCollisionEnter2D(Collision2D collision)
    {
        
    }
}
