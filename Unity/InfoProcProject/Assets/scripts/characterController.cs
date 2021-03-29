using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class characterController : MonoBehaviour
{
    Transform m_position;
    //Collider2D m_collider;
    float vertical;
    float horizontal;
    Vector3 newPosition;
    Vector3 initialPosition;
    [SerializeField] float speed = 5f;
    Animator animator;
    float previous_ver;
    float previous_hor;
    bool fire;
    bool setbomb = false;
    public string x;
    char x2;
    public bool bombed = false;
    float shottimer = 2f;
    float bombtimer = 2f;


    [SerializeField] GameObject bombgameobject;
    [SerializeField] GameObject fire_up;
    [SerializeField] GameObject fire_left;
    [SerializeField] GameObject fire_right;
    [SerializeField] GameObject fire_down;
    [SerializeField] GameObject bullet;

    public bool isrunning = false;
    // Start is called before the first frame update
    void Start()
    {
        m_position = GetComponent<Transform>();
        initialPosition = GetComponent<Transform>().position;
        //m_collider = GetComponent<Collider2D>();
        animator = GetComponent<Animator>();
    }

    // Update is called once per frame
    void Update()
    {
        if (isrunning)
        {
            horizontal = Input.GetAxisRaw("ChaserHorizontal");
            vertical = Input.GetAxisRaw("ChaserVertical");
            fire = Input.GetKeyDown("space");
            setbomb = Input.GetKeyDown("r");
            animator.SetBool("shot", false);
            if (!string.IsNullOrEmpty(x))
            {
                if (x[0] == 'x')
                {
                    x2 = x[1];
                }
            }
            if (x2 == 'w')
            {
                vertical = 1;
                horizontal = 0;
            }
            else if (x2 == 's')
            {
                vertical = -1;
                horizontal = 0;
            }
            else if (x2 == 'a')
            {
                horizontal = -1;
                vertical = 0;
            }
            else if (x2 == 'd')
            {
                horizontal = 1;
                vertical = 0;
            }
            else if (x2 == 'e')
            {
                horizontal = 0;
                vertical = 0;
                fire = true;
            }
            else if (x2 == 'r')
            {
                horizontal = 0;
                vertical = 0;
                setbomb = true;
            }
            if (fire == true)
            {
                if (!bombed)
                {
                    shottimer = 2f;
                    if (animator.GetCurrentAnimatorStateInfo(0).IsName("redleft"))
                    {
                        Instantiate(fire_left, transform.position + (Vector3.left * 0.5f) + Vector3.forward, transform.rotation);
                        Instantiate(bullet, transform.position + (Vector3.left * 0.5f) + Vector3.forward, Quaternion.Euler(0f, 0f, 180f));
                    }
                    else if (animator.GetCurrentAnimatorStateInfo(0).IsName("redright"))
                    {
                        Instantiate(fire_right, transform.position + (Vector3.right * 0.5f) + Vector3.forward, transform.rotation);
                        Instantiate(bullet, transform.position + (Vector3.right * 0.5f) + Vector3.forward, Quaternion.Euler(0f, 0f, 0f));
                    }
                    else if (animator.GetCurrentAnimatorStateInfo(0).IsName("reddown"))
                    {
                        Instantiate(fire_down, transform.position + (Vector3.down * 0.5f) + Vector3.forward, transform.rotation);
                        Instantiate(bullet, transform.position + (Vector3.down * 0.5f) + Vector3.forward, Quaternion.Euler(0f, 0f, 270f));
                    }
                    else if (animator.GetCurrentAnimatorStateInfo(0).IsName("redup"))
                    {
                        Instantiate(fire_up, transform.position + (Vector3.up * 0.5f) + Vector3.forward, transform.rotation);
                        Instantiate(bullet, transform.position + (Vector3.up * 0.5f) + Vector3.forward, Quaternion.Euler(0f, 0f, 90f));
                    }
                    animator.SetBool("shot", true);
                    fire = false;
                }
                else
                {
                    if (shottimer < 0)
                    {
                        if (animator.GetCurrentAnimatorStateInfo(0).IsName("redleft"))
                        {
                            Instantiate(fire_left, transform.position + (Vector3.left * 0.5f) + Vector3.forward, transform.rotation);
                            Instantiate(bullet, transform.position + (Vector3.left * 0.5f) + Vector3.forward, Quaternion.Euler(0f, 0f, 180f));
                        }
                        else if (animator.GetCurrentAnimatorStateInfo(0).IsName("redright"))
                        {
                            Instantiate(fire_right, transform.position + (Vector3.right * 0.5f) + Vector3.forward, transform.rotation);
                            Instantiate(bullet, transform.position + (Vector3.right * 0.5f) + Vector3.forward, Quaternion.Euler(0f, 0f, 0f));
                        }
                        else if (animator.GetCurrentAnimatorStateInfo(0).IsName("reddown"))
                        {
                            Instantiate(fire_down, transform.position + (Vector3.down * 0.5f) + Vector3.forward, transform.rotation);
                            Instantiate(bullet, transform.position + (Vector3.down * 0.5f) + Vector3.forward, Quaternion.Euler(0f, 0f, 270f));
                        }
                        else if (animator.GetCurrentAnimatorStateInfo(0).IsName("redup"))
                        {
                            Instantiate(fire_up, transform.position + (Vector3.up * 0.5f) + Vector3.forward, transform.rotation);
                            Instantiate(bullet, transform.position + (Vector3.up * 0.5f) + Vector3.forward, Quaternion.Euler(0f, 0f, 90f));
                        }
                        shottimer = 2f;
                        animator.SetBool("shot", true);
                        fire = false;
                    }
                    else
                    {
                        shottimer -= Time.deltaTime;
                    }
                }
            }
            else if (setbomb == true)
            {
                if (bombtimer < 0)
                {
                    Instantiate(bombgameobject, transform.position, Quaternion.Euler(0f, 0f, 0f));
                    bombtimer = 2f;
                }
                else { }
            }
            bombtimer -= Time.deltaTime;

            if (horizontal != previous_hor || vertical != previous_ver)
            {
                animator.SetFloat("horizontal", horizontal);
                animator.SetFloat("vertical", vertical);
            }
            newPosition = new Vector3(horizontal, vertical, 0);
            m_position.position += newPosition * Time.deltaTime * speed;
            previous_hor = horizontal;
            previous_ver = vertical;
        }
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.CompareTag("runner"))
        {
            m_position.position = initialPosition;
        }
    }
}
