export default async function PostDetails({ postId }) {
  await new Promise((resolve) => {
    setTimeout(() => {
      resolve();
    }, 2000);
  });
  const response = await fetch(
    `https://jsonplaceholder.typicode.com/posts/${postId}`,
    {
      next: {
        revalidate: 120,
      },
    }
  );
  const post = await response.json();
  return (
    <div>
      <div
        style={{
          backgroundColor: "white",
          color: "black",
          padding: "10px",
          margin: "10px",
          width: "70%",
        }}
      >
        <h1 style={{ color: "red" }}>{post.title}</h1>
        <p>{post.body}</p>
      </div>
    </div>
  );
}
