const fs = require('fs');
const path = require('path');

const rootDir = path.resolve('src');

// Collect all header files with paths relative to rootDir
function collectHeaders(dir, base = '', headers = {}) {
  const files = fs.readdirSync(dir);
  for (const file of files) {
    const fullPath = path.join(dir, file);
    const stat = fs.statSync(fullPath);
    if (stat.isDirectory()) {
      collectHeaders(fullPath, path.join(base, file), headers);
    } else if (file.endsWith('.h')) {
      headers[file] = path.join(base, file).replace(/\\/g, '/'); // path relative to src/
    }
  }
  return headers;
}

const headersMap = collectHeaders(rootDir);

function fixIncludes(dir) {
  const files = fs.readdirSync(dir);

  for (const file of files) {
    const fullPath = path.join(dir, file);
    const stat = fs.statSync(fullPath);

    if (stat.isDirectory()) {
      fixIncludes(fullPath);
      continue;
    }

    if (!file.endsWith('.cpp') && !file.endsWith('.h')) continue;

    let content = fs.readFileSync(fullPath, 'utf8');
    let modified = false;

    content = content.replace(/#include ["<](.*?)[">]/g, (match, includeFile) => {
      // Ignore system headers
      if (includeFile.includes('/')) return match;

      // Check if header exists in headersMap
      if (headersMap[includeFile]) {
        const newPath = headersMap[includeFile]; // relative to src/
        if (newPath !== includeFile) {
          const folderPath2 = path.basename(path.dirname(fullPath));
          modified = true;
          return `#include "${newPath.replace("./", folderPath2.replace("src/", "").replace("/", "") + "/")}"`;
        }
      }
      return match;
    });

    if (modified) fs.writeFileSync(fullPath, content, 'utf8');
  }
}

fixIncludes(rootDir);
console.log('Include paths fixed!');
