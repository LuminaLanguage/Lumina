const fs = require('fs');
const path = require('path');

const rootDir = path.resolve('src');

// Collect all headers in src/ recursively
function collectHeaders(dir, headers = {}) {
  const files = fs.readdirSync(dir);
  for (const file of files) {
    const fullPath = path.join(dir, file);
    const stat = fs.statSync(fullPath);
    if (stat.isDirectory()) collectHeaders(fullPath, headers);
    else if (file.endsWith('.h')) headers[file] = fullPath;
  }
  return headers;
}

const headersMap = collectHeaders(rootDir);

function fixIncludes(dir) {
  const files = fs.readdirSync(dir);
  for (const file of files) {
    const fullPath = path.join(dir, file);
    const stat = fs.statSync(fullPath);
    if (stat.isDirectory()) { fixIncludes(fullPath); }
    else if (file.endsWith('.cpp') || file.endsWith('.h')) {
      let content = fs.readFileSync(fullPath, 'utf8');

      content = content.replace(/#include ["<](.*?)[">]/g, (match, includeFile) => {
        if (headersMap[includeFile]) {
          // Compute relative path from current file to header
          const relativePath = path.relative(path.dirname(fullPath), headersMap[includeFile]).replace(/\\/g, '/');
          return `#include "${relativePath}"`;
        }
        return match; // leave system or unknown includes as-is
      });

      fs.writeFileSync(fullPath, content, 'utf8');
    }
  }
}

fixIncludes(rootDir);
console.log('Include paths fixed!');
