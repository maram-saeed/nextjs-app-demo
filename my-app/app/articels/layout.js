export const metadata = {
    title: "articels page"
}

export default function ({ children }) {
    return (
        <div>
            <h1>Layout Articels</h1>
            <div style={{ marginTop: "50px", background: "blue", padding: "20px", borderRadius: "10px" }}>
                {children}
            </div>
        </div>
    );
}